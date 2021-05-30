#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

const int width = 800;
const int height = 600;
int deg = 0;
float brightness = 0.75;
float amb_perc = 0.3;

bool flagScale=true;
bool light1 = false;
bool light2 = false;
bool light3 = false;
bool ambient = true;
bool diffuse = true;
bool specular = true;

GLfloat eyeX = 0;
GLfloat eyeY = 10;
GLfloat eyeZ = -20;

GLfloat lookX = 0;
GLfloat lookY = 8;
GLfloat lookZ = 0;

float rot = 0;
const float r = 1.0 * width / height;

static void resize(int width, int height)
{
     glViewport(0, 0, width, width/r);
}

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

static GLfloat cube_points[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte surface[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

void cube(float r=0.5, float g=0.5, float b=0.5, float alpha=1)
{
    //GLfloat m_no[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat material_ambient[] = {r*amb_perc*brightness,g*amb_perc*brightness,b*amb_perc*brightness,1.0};
    GLfloat material_diffuse[] = {r*brightness,g*brightness,b*brightness,1.0};
    GLfloat material_specular[] = {1,1,1,1.0};
    GLfloat material_shininess[] = {90};

    //GLfloat m_emission[] = {1.0,1.0,1.0,1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    /*if(light == 1){
        if(emission && light1) glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
        else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }
    else if(light == 2){
        if(emission && light2) glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
        else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }
    else if(light == 3){
        if(emission && light3) glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
        else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }*/

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor4f(colR,colG,colB,alpha);

        //colR += 0.03;
        //colG += 0.03;
        //olB += 0.03;
        getNormal3p(cube_points[surface[i][0]][0], cube_points[surface[i][0]][1], cube_points[surface[i][0]][2],
                    cube_points[surface[i][1]][0], cube_points[surface[i][1]][1], cube_points[surface[i][1]][2],
                    cube_points[surface[i][2]][0], cube_points[surface[i][2]][1], cube_points[surface[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&cube_points[surface[i][j]][0]);
        }
    }
    glEnd();
}

static GLfloat prism_points[6][3] =
{
    {1,0,0},
    {-0.5,0,0.87},
    {-0.5,0,-0.87},
    {1,1,0},
    {-0.5,1,0.87},
    {-0.5,1,-0.87}
};

static GLubyte prism_triangle_suface[2][3] =
{
    {0,2,1},
    {3,4,5}
};

static GLubyte prism_rectangle_suface[3][4] =
{
    {2,5,4,1},
    {0,3,5,2},
    {1,4,3,0}
};

void prism(float r=0.5, float g=0.5, float b=0.5, float alpha=1)
{
    //GLfloat m_no[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat material_ambient[] = {r*amb_perc*brightness,g*amb_perc*brightness,b*amb_perc*brightness,1.0};
    GLfloat material_diffuse[] = {r*brightness,g*brightness,b*brightness,1.0};
    GLfloat material_specular[] = {1,1,1,1.0};
    GLfloat material_shininess[] = {90};

    //GLfloat m_emission[] = {1.0,1.0,1.0,1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    glBegin(GL_TRIANGLES);
    for(int i = 0; i<2;i++)
    {
        getNormal3p(prism_points[prism_triangle_suface[i][0]][0],
                    prism_points[prism_triangle_suface[i][0]][1],
                    prism_points[prism_triangle_suface[i][0]][2],
                    prism_points[prism_triangle_suface[i][1]][0],
                    prism_points[prism_triangle_suface[i][1]][1],
                    prism_points[prism_triangle_suface[i][1]][2],
                    prism_points[prism_triangle_suface[i][2]][0],
                    prism_points[prism_triangle_suface[i][2]][1],
                    prism_points[prism_triangle_suface[i][2]][2]
                    );
        for(int j =0; j<3; j++)
        {
            glVertex3fv(&prism_points[prism_triangle_suface[i][j]][0]);
        }
    }
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    glBegin(GL_QUADS);
    for(int i = 0; i<3;i++)
    {
        getNormal3p(prism_points[prism_rectangle_suface[i][0]][0],
                    prism_points[prism_rectangle_suface[i][0]][1],
                    prism_points[prism_rectangle_suface[i][0]][2],
                    prism_points[prism_rectangle_suface[i][1]][0],
                    prism_points[prism_rectangle_suface[i][1]][1],
                    prism_points[prism_rectangle_suface[i][1]][2],
                    prism_points[prism_rectangle_suface[i][2]][0],
                    prism_points[prism_rectangle_suface[i][2]][1],
                    prism_points[prism_rectangle_suface[i][2]][2]
                    );
        for(int j =0; j<4; j++)
        {
            glVertex3fv(&prism_points[prism_rectangle_suface[i][j]][0]);
        }
    }
    glEnd();
}

void cylinder(float r=0.5, float g=0.5, float b=0.5, int slice = 180, float height = 3, float radius = 1)
{
    for(int i=0;i<=360;i+=360/slice)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        glRotatef(180,0,1,0);
        glScalef(radius/1.41,height,1);
        glTranslatef(-1,0,0);
        prism(r,g,b);
        glPopMatrix();
    }
}

void tubeLight1(float xPos, float yPos, float zPos)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { xPos, yPos, zPos, 1.0 };

    glEnable( GL_LIGHT0);
    if(light1){
        if(ambient)
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        }
        else{
            glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        }

        if(diffuse)
        {
            glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        }
        else{
            glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        }

        if(specular)
        {
            glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        }
        else{
            glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
        }

    }
    else{
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
    }
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
}

void tubeLight2(float xPos, float yPos, float zPos)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { xPos, yPos, zPos, 1.0 };

    glEnable( GL_LIGHT1);
    if(light2){
        if(ambient)
        {
            glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
        }
        else{
            glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
        }

        if(diffuse)
        {
            glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
        }
        else{
            glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
        }

        if(specular)
        {
            glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
        }
        else{
            glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
        }

    }
    else{
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
    }

    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
}

void spotLight(float xPos, float yPos, float zPos)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.0, 0.0, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_position[] = { xPos, yPos, zPos, 1.0 };
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    GLfloat spot_cutOff[] = {60.0};

    glEnable( GL_LIGHT2);
    if(light3){
        if(ambient)
        {
            glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
        }
        else{
            glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
        }

        if(diffuse)
        {
            glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
        }
        else{
            glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
        }

        if(specular)
        {
            glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
        }
        else{
            glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
        }

    }
    else{
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
    }

    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightfv( GL_LIGHT2, GL_SPOT_CUTOFF, spot_cutOff);
}

void axes()
{
    float length = 10;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.8,0.1,0.1);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.8,0.1);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.1,0.8);
    glPopMatrix();
}

void floorWallsCeiling(float scale)
{
    // floor
    glPushMatrix();
    glScalef(scale,1,scale);
    glTranslatef(-0.5,-1,-0.5);
    cube(1.000, 0.980, 0.980);  //snow
    glPopMatrix();

    //left wall
    glPushMatrix();
    glTranslatef(scale/2,scale/4,0);
    glScalef(1,scale/2,scale);
    glTranslatef(-1,-0.5,-0.5);
    cube(0.871, 0.722, 0.529); // burly wood
    glPopMatrix();

    //right wall
    glPushMatrix();
    glTranslatef(-scale/2+1,scale/4,0);
    glScalef(1,scale/2,scale);
    glTranslatef(-1,-0.5,-0.5);
    cube(0.871, 0.722, 0.529);  // burly wood
    glPopMatrix();

    //back wall
    glPushMatrix();
    glTranslatef(0,scale/4,scale/2);
    glScalef(scale,scale/2,1);
    glTranslatef(-0.5,-0.5,-1);
    cube(1.000, 0.855, 0.725); // PeachPu
    glPopMatrix();

    //ceiling
    glPushMatrix();
    glTranslatef(0,scale/2,0);
    glScalef(scale,1,scale);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.871, 0.722, 0.529);  // burly wood
    glPopMatrix();
}

void fan()
{
    float length =.3;
    float height =3.5;
    float width =0.05;

    float wall_height =15.0;
    float wall_z= 7;

    float blade_length =5.5;
    float blade_height =0.15;
    float blade_width =0.4;


    glPushMatrix();
    glRotatef(deg,0,1,0);

    glPushMatrix();
    glTranslatef(0,wall_height-height,0);
    glScalef(blade_width,blade_height,blade_length);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,wall_height-height,0);
    glScalef(blade_length,blade_height,blade_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,wall_height,0);
    glScalef(width,height,length);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    for (int i=1; i<=360; i++)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        glTranslatef(0,wall_height-height,0);
        glScalef(1,blade_height*1.3,0.5);
        glTranslatef(-0.5,-1,-0.5);
        cube(0.502, 0.000, 0.000);
        glPopMatrix();
    }

}

void window(float width = 4, float length = 6)
{
    glPushMatrix();
    glScalef(width,length,0.1);
    glTranslatef(-0.5,0,-0.5);
    cube(0.545,0.271,0.075); //saddle brown
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,(length-length*0.8)/2,-(0.1/2-0.05/2)-0.01);
    glScalef(width*0.8,length*0.8,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0.941, 1.000, 1.000); //Azure
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,(length-length*0.8)/2,-(0.1/2-0.05/2)-0.02);
    glScalef(0.2,length*0.8,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //Black
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,((length-length*0.8)/2)+((length*0.8)/4),-(0.1/2-0.05/2)-0.02);
    glScalef(width*0.8,0.2,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //Black
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,((length-length*0.8)/2)+2*((length*0.8)/4),-(0.1/2-0.05/2)-0.02);
    glScalef(width*0.8,0.2,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //Black
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,((length-length*0.8)/2)+3*((length*0.8)/4),-(0.1/2-0.05/2)-0.02);
    glScalef(width*0.8,0.2,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //Black
    glPopMatrix();
}

void wardrobe(float drawerHeight = 3, float drawerWidth = 4, float drawerLength = 3,int numOfDrawer = 2)
{
    int height = 0;
    for(int i = 0; i<numOfDrawer; i++)
    {
        glPushMatrix();
        glTranslatef(0,height,0);

        glPushMatrix();
        glScalef(drawerWidth,drawerHeight,drawerLength);
        glTranslatef(-0.5,0,-0.5);
        cube(0.545,0.271,0.075); //saddle brown
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-drawerLength/2-0.1/2);
        glScalef(drawerWidth-0.6,drawerHeight-0.3, 0.1);
        glTranslatef(-0.5,0,-0.5);
        cube(0.804, 0.522, 0.247); // peru
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,drawerHeight/2-0.1/2,-drawerLength/2-0.15/2);
        glScalef(drawerWidth/4,drawerHeight/8, 0.1);
        glTranslatef(-0.5,0,-0.5);
        cube(0.96, 1, 0.98); //mint white
        glPopMatrix();

        glPopMatrix();

        height += drawerHeight;
    }

    drawerWidth += 0.6;
    drawerLength += 0.45;
    for(int i=0; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(0,height,0);
        glScalef(drawerWidth,0.3,drawerLength);
        glTranslatef(-0.5,0,-0.5);
        cube(0.545,0.271,0.075); //saddle brown
        glPopMatrix();

        height += 0.3;
        drawerWidth -= 0.1;
        drawerLength -= 0.1;

    }

}

void dressingTable(float drawerHeight = 2, float drawerWidth = 3, float drawerLength = 2,int numOfDrawer = 3)
{
    int height = 0;
    for(int i = 0; i<numOfDrawer; i++)
    {
        glPushMatrix();
        glTranslatef(0,drawerWidth/2,0);
        glRotatef(90,1,0,0);
        glRotatef(90,0,1,0);
        glTranslatef(0,height,0);

        glPushMatrix();
        glScalef(drawerWidth,drawerHeight,drawerLength);
        glTranslatef(-0.5,0,-0.5);
        cube(0.545,0.271,0.075); //saddle brown
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-drawerLength/2-0.1/2);
        glScalef(drawerWidth-0.6,drawerHeight-0.3, 0.1);
        glTranslatef(-0.5,0,-0.5);
        cube(0.804, 0.522, 0.247); //peru
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,drawerHeight/8,-drawerLength/2-0.15/2);
        glScalef(drawerWidth/4,drawerHeight/8, 0.1);
        glTranslatef(-0.5,0,-0.5);
        cube(0.96, 1, 0.98); //mint white
        glPopMatrix();

        glPopMatrix();

        height += drawerHeight;
    }

    glPushMatrix();
    glTranslatef(drawerLength/2-0.1/2,drawerWidth,(drawerHeight*numOfDrawer)/2);
    glScalef(0.1,5.5,(drawerHeight*numOfDrawer)*0.8);
    glTranslatef(-0.5,0,-0.5);
    cube(0.545,0.271,0.075); //saddlebrown
    glPopMatrix();

    glPushMatrix();
    glTranslatef(drawerLength/2-0.1/2-0.05,drawerWidth+(4-4*0.8)/2,(drawerHeight*numOfDrawer)/2);
    glScalef(0.05,5.5*0.8,(drawerHeight*numOfDrawer)*0.8*0.9);
    glTranslatef(-0.5,0,-0.5);
    cube(0.941, 1.000, 1.000); //Azure
    glPopMatrix();

}

void clock(float width = 3, float length = 4)
{
    glPushMatrix();
    glScalef(width,length,0.1);
    glTranslatef(-0.5,0,-0.5);
    cube(0.275, 0.510, 0.706); //steel blue
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,(length-length*0.9)/2,-(0.1/2-0.05/2)-0.05);
    glScalef(width*0.9,length*0.9,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0.941, 1.000, 1.000); //Azure
    glPopMatrix();

    //hour
    glPushMatrix();
    glTranslatef(0,length/2,-(0.1/2-0.05/2)-0.06);
    glScalef(0.05,0.8,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //black
    glPopMatrix();

    //minute
    glPushMatrix();
    glTranslatef(-1.2/2,length/2,-(0.1/2-0.05/2)-0.06);
    glScalef(1.2,0.05,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //black
    glPopMatrix();

    //second
    glPushMatrix();
    glTranslatef(0.5,length/2-0.8,-(0.1/2-0.05/2)-0.06);
    glRotatef(30,0,0,1);
    glScalef(0.05,1,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //black
    glPopMatrix();

}

void bed()
{
    float baseHeight = 3;
    float width = 9;
    float length = 13;
    float pillowWidth = 3;
    float pillowLength = 1.5;
    float blanketWidth = 8;
    float blanketLength = 7;
    float headHeight = 6;
    float drawerWidth = 5;
    float drawerLength = 2;
    float handleWidth = 1.5;
    float handleLength = 0.5;

    //base
    glPushMatrix();
    glScalef(width,baseHeight,length);
    glTranslatef(-0.5,0,-0.5);
    cube(0.545,0.271,0.075); //saddlebrown
    glPopMatrix();

    //foam
    glPushMatrix();
    glTranslatef(0,baseHeight,0);
    glScalef(width,0.6,length);
    glTranslatef(-0.5,0,-0.5);
    cube(0.804,0.361,0.361); //indian red
    glPopMatrix();

    //pillow 1
    glPushMatrix();
    glTranslatef((width/2)-(1+pillowWidth/2),baseHeight+1*0.6,(length/2)-(0.25+pillowWidth/2));
    glScalef(pillowWidth,0.4,pillowLength);
    glTranslatef(-0.5,0,-0.5);
    cube(1,0.647,0); // orange
    glPopMatrix();

    // pillow 2
    glPushMatrix();
    glTranslatef(-(width/2)+(1+pillowWidth/2),baseHeight+1*0.6,(length/2)-(0.25+pillowWidth/2));
    glScalef(pillowWidth,0.4,pillowLength);
    glTranslatef(-0.5,0,-0.5);
    cube(1,0.647,0); // orange
    glPopMatrix();

    //blanket
    glPushMatrix();
    glTranslatef(0,baseHeight+1*0.6,-(length/2-0.25)+blanketLength/2);
    glScalef(blanketWidth,0.15,blanketLength);
    glTranslatef(-0.5,0,-0.5);
    cube(0.541,0.169,0.886); // blue violet
    glPopMatrix();

    //head
    glPushMatrix();
    glTranslatef(0,0,(length/2-0.2/2)+0.2);
    glScalef(width,headHeight,0.2);
    glTranslatef(-0.5,0,-0.5);
    cube(0.545,0.271,0.075); // saddle brown
    glPopMatrix();

    // drawer 1
    glPushMatrix();
    glTranslatef(-(width/2-0.05/2),0.5,-(length/2-drawerWidth/2)+1);
    glScalef(0.1,drawerLength,drawerWidth);
    glTranslatef(-0.5,0,-0.5);
    cube(0.627,0.322,0.176); // sienna
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(width/2-0.03/2),0.5+0.75,-(length/2-drawerWidth/2)+1); //+(drawerWidth/2-handleWidth/2)
    glScalef(0.1,handleLength,handleWidth);
    glTranslatef(-0.5,0,-0.5);
    cube(0.941,0.502,0.502); // light coral
    glPopMatrix();

    // drawer 2
    glPushMatrix();
    glTranslatef(-(width/2-0.05/2),0.5,(length/2-drawerWidth/2)-1);
    glScalef(0.1,drawerLength,drawerWidth);
    glTranslatef(-0.5,0,-0.5);
    cube(0.627,0.322,0.176); // sienna
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(width/2-0.03/2),0.5+0.75,(length/2-drawerWidth/2)-1); //+(drawerWidth/2-handleWidth/2)
    glScalef(0.1,handleLength,handleWidth);
    glTranslatef(-0.5,0,-0.5);
    cube(0.941,0.502,0.502); // light coral
    glPopMatrix();


}

void mat()
{
    glPushMatrix();
    glScalef(0.5,0.1,5);
    glTranslatef(-0.5,0,-0.5);
    cube(1.000, 0.000, 1.000);  // Magenta
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,0,0);
    glScalef(0.5,0.1,5);
    glTranslatef(-0.5,0,-0.5);
    cube(1.000, 0.388, 0.278);  // Tomato
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5*2,0,0);
    glScalef(0.5,0.1,5);
    glTranslatef(-0.5,0,-0.5);
    cube(0.294, 0.000, 0.510);  // Indigo
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5*3,0,0);
    glScalef(0.5,0.1,5);
    glTranslatef(-0.5,0,-0.5);
    cube(1.000, 0.388, 0.278);  // Tomato
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5*4,0,0);
    glScalef(0.5,0.1,5);
    glTranslatef(-0.5,0,-0.5);
    cube(1.000, 0.000, 1.000);  // Magenta
    glPopMatrix();

}

void tubeLightObj(float length = 6, float height = 0.25, float width = 0.85, float r = 0.8, float g = 0.8, float b = 0.8)
{
    glPushMatrix();
    glScalef(height,width,length);
    glTranslatef(-0.5,0,-0.5);
    cube(r,g,b);
    glPopMatrix();
}

void tableLamp(float r = 0.5, float g = 0.5,float b = 0.5, float radius = 1.0, int slices = 20, int stacks = 20, float width = 2.5, float height = 0.3, float length = 2)
{
     //GLfloat m_no[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat material_ambient[] = {r*amb_perc*brightness,g*amb_perc*brightness,b*amb_perc*brightness,1.0};
    GLfloat material_diffuse[] = {r*brightness,g*brightness,b*brightness,1.0};
    GLfloat material_specular[] = {1,1,1,1.0};
    GLfloat material_shininess[] = {90};

    //GLfloat m_emission[] = {1.0,1.0,1.0,1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    /*if(light == 1){
        if(emission && light1) glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
        else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }
    else if(light == 2){
        if(emission && light2) glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
        else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }
    else if(light == 3){
        if(emission && light3) glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
        else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }*/

    glPushMatrix();
    glPushMatrix();
    glTranslatef(0,radius+height,0);
    glutSolidSphere(radius,slices,stacks);
    glPopMatrix();
    glScalef(width,height,length);
    glTranslatef(-0.5,0,-0.5);
    cube(0.647, 0.165, 0.165);  // Brown
    glPopMatrix();
}

void tool(float legHeight = 2.8, float legWidth = 2.2, float legD = 0.3, float legGap = 2, float baseD = 0.2)
{
    //left leg
    glPushMatrix();
    glTranslatef(legGap/2+legD/2,0,0);
    glScalef(legD,legHeight,legWidth);
    glTranslatef(-0.5,0,-0.5);
    cube(0.545,0.271,0.075); //saddlebrown
    glPopMatrix();

    //right leg
    glPushMatrix();
    glTranslatef(-legGap/2-legD/2,0,0);
    glScalef(legD,legHeight,legWidth);
    glTranslatef(-0.5,0,-0.5);
    cube(0.545,0.271,0.075); //saddlebrown
    glPopMatrix();

    // base
    glPushMatrix();
    glTranslatef(0,legHeight*0.7,0);
    glScalef(legGap,baseD,legWidth*0.9);
    glTranslatef(-0.5,0,-0.5);
    cube(0.804, 0.522, 0.247); //peru
    glPopMatrix();

    //foam
    glPushMatrix();
    glTranslatef(0,(legHeight*0.7)+baseD,0);
    glScalef(legGap,legHeight-(legHeight*0.7)-baseD+0.1,legWidth*0.9);
    glTranslatef(-0.5,0,-0.5);
    cube(1,1,1); //white
    glPopMatrix();

}

void readingTable(float legHeight = 3.5, float legWidth = 3, float legD = 0.3, float legGap = 5, float baseD = 0.2)
{
    //left leg
    glPushMatrix();
    glTranslatef(legGap/2+legD/2,0,0);
    glScalef(legD,legHeight,legWidth);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // Chocolate color
    glPopMatrix();

    //right leg
    glPushMatrix();
    glTranslatef(-legGap/2-legD/2,0,0);
    glScalef(legD,legHeight,legWidth);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    //back
    glPushMatrix();
    glTranslatef(0,legHeight-legHeight*0.7,legWidth/2-legD/4);
    glScalef(legGap,legHeight*0.7,legD/2);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    // table surface
    glPushMatrix();
    glTranslatef(0,legHeight-baseD,0);
    glScalef(legGap*1.2,baseD,legWidth*1.1);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    //bottom shelve
    glPushMatrix();
    glTranslatef(0,legHeight-legHeight*0.7-baseD,legWidth/2-(legWidth*0.6)/2);
    glScalef(legGap,baseD,legWidth*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    // table drayer
    glPushMatrix();
    glTranslatef(0,legHeight-legHeight/7-legHeight/14,-legWidth/2-baseD/8);
    glScalef(legGap*1.05,legHeight/7,baseD);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,legHeight-legHeight/7-legHeight/14,-legWidth/2-baseD/2-0.1/2);
    glScalef(0.8,0.3,0.1);
    glTranslatef(-0.5,0,-0.5);
    cube(0.8,0.8,0.8);
    glPopMatrix();

}

void bookShelf()
{
    glPushMatrix();
    glScalef(5.6,0.3,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2,0);
    glScalef(5.6,0.3,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5,0,0);
    glScalef(0.2,2,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,0,0);
    glScalef(0.2,2,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,0,0);
    glScalef(0.1,2,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,0,0);
    glScalef(0.1,2,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1,2,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5/2-1/2-0.75,1,0);
    glScalef(1,0.05,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5/2+1/2+0.75,1,0);
    glScalef(1,0.05,2.2*0.6);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118); // chocolate color
    glPopMatrix();

}

void book(float r = 0, float g = 1, float b = 0, float width = 0.8, float length = 1.2, float height = 0.3)
{
    //pages
    glPushMatrix();
    glScalef(width,height,length);
    glTranslatef(-0.5,0,-0.5);
    cube(1,1,1);
    glPopMatrix();

    // front cover
    glPushMatrix();
    glTranslatef(0,height,0);
    glScalef(1.2*width,0.05,1.2*length);
    glTranslatef(-0.5,0,-0.5);
    cube(r,g,b);
    glPopMatrix();

    // back cover
    glPushMatrix();
    glScalef(1.2*width,0.05,1.2*length);
    glTranslatef(-0.5,0,-0.5);
    cube(r,g,b);
    glPopMatrix();

    //left cover
    glPushMatrix();
    glTranslatef((1.2*width/2)-0.05/2,0,0);
    glScalef(0.05,height+(2*0.05),length*1.2);
    glTranslatef(-0.5,0,-0.5);
    cube(r,g,b);
    glPopMatrix();
}

void chair()
{
    float height=2;
    float width=2;
    float length=2;

    float base_height=0.3;
    float leg_height=height-base_height;
    float leg_width=0.2;

    // whole table
    glPushMatrix();
    glTranslatef(0,leg_height,0);

    // base
    glPushMatrix();
    glScalef(width,base_height,length);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    // legs
    glPushMatrix();
    glTranslatef((width/2-leg_width/2),0,(length/2-leg_width/2));
    glScalef(leg_width,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((width/2-leg_width/2),0,-(length/2-leg_width/2));
    glScalef(leg_width,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(width/2-leg_width/2),0,(length/2-leg_width/2));
    glScalef(leg_width,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(width/2-leg_width/2),0,-(length/2-leg_width/2));
    glScalef(leg_width,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(width/2-leg_width/2,0,length/2-leg_width/2);
    glScalef(leg_width,1.6*height,leg_width);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(width/2-leg_width/2),0,length/2-leg_width/2);
    glScalef(leg_width,1.6*height,leg_width);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.6*height,length/2-leg_width/2);
    glScalef(width,leg_width,leg_width);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,(1.6*height)/3,length/2-leg_width/2);
    glScalef(width,leg_width,leg_width);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2*(1.6*height)/3,length/2-leg_width/2);
    glScalef(width,leg_width,leg_width);
    glTranslatef(-0.5,0,-0.5);
    cube(0.824, 0.412, 0.118);
    glPopMatrix();

    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2, 2, -2, 2, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);
    //glViewport(0, 0, width, height);

    glRotatef(rot, 0,1,0);

    //axes();

    /*glPushMatrix();
    glTranslatef(0,0,-3);
    cylinder(0.3,0.1,0.7,72,2,1);
    glPopMatrix();*/

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,0,-4);
    glRotatef(-90,0,1,0);
    readingTable();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,3.7,-2.5);
    book(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,3.7+0.4,-2.5);
    book(0,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,3.7+0.8,-2.5);
    book(1,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,3.7,-6);
    glRotatef(-90,0,1,0);
    book(1,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,3.7+0.4,-6);
    glRotatef(-90,0,1,0);
    book(0,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,3.7+0.8,-6);
    glRotatef(-90,0,1,0);
    book(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,8,-4.3);
    glRotatef(-75,1,0,0);
    book(1,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,8,-4.7);
    glRotatef(-75,1,0,0);
    book(0,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,8,-3.4);
    glRotatef(90,1,0,0);
    book(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,8,-3.6);
    glRotatef(-90,1,0,0);
    book(0.863, 0.078, 0.235);  // crimson
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,8,-3.0);
    glRotatef(90,1,0,0);
    book(0.180, 0.545, 0.341); // sea green
    glPopMatrix();

    glPushMatrix();
    glTranslatef((-30/2+1+(2.2*1.1)/2)+3.5,0,-4);
    glRotatef(90,0,1,0);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30/2+1+(2.2*1.1)/2,7,-4);
    glRotatef(-90,0,1,0);
    bookShelf();
    glPopMatrix();

    tubeLight1(-15+1,12,-7);
    glPushMatrix();
    glTranslatef(-15+1+0.25/2,12,-7);
    tubeLightObj(6,0.25,0.85); // create tubelight 1 here
    glPopMatrix();

    tubeLight2(15-1,12,-7);
    glPushMatrix();
    glTranslatef(15-1-0.25/2,12,-7);
    tubeLightObj(6,0.25,0.85); // create tubelight 2 here
    glPopMatrix();

    spotLight(-11.85,6.5,(30/2-3.5/2)-2.5);
    glPushMatrix();
    glTranslatef(-11.85,4.5,(30/2-3.5/2)-1.6);
    tableLamp(0.275, 0.510, 0.706);  // SteelBlue
    glPopMatrix();

    floorWallsCeiling(30);
    fan();

    glPushMatrix();
    glTranslatef(-4,0,(30/2-13/2)-1.6);
    bed();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12,0,(30/2-3.5/2)-1.6);
    wardrobe(2,4,3.5,2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7,0,(30/2-3.5/2)-1.6);
    wardrobe(3,8,3.5,3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5,0,3.5);
    mat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30/2-4/2,0,-6);
    dressingTable(2,4,2,3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30/2-4/2-2-2,0,-3);
    glRotatef(90,0,1,0);
    tool();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,10,30/2-3/2);
    clock(3,3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11,8,30/2-3/2);
    window(5,5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30/2-3/2,6,4);
    glRotatef(90,0,1,0);
    window(8,7);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    //case 27 :

    case 'l':
        rot++;
        break;

    case 'j':
        rot--;
        break;

    case 'i':
        eyeY++;
        break;

    case 'k':
        eyeY--;
        break;

    case 'z':
        eyeZ++;
        lookZ++;
        break;

    case 'x':
        eyeZ--;
        lookZ--;
        break;

    case 'o':
        flagScale=true;
        break;

    case 'p':
        flagScale=false;
        break;

    case '1':
        light1 = !light1;
        break;

    case '2':
        light2 = !light2;
        break;

    case '3':
        light3 = !light3;
        break;

    case 'a':
        ambient = !ambient;
        break;

    case 'd':
        diffuse = !diffuse;
        break;

    case 's':
        specular = !specular;
        break;

    case 'q':
        exit(0);
        break;

    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

void animate()
{
    if (flagScale == true)
    {
        deg+= 2;
        if(deg > 360)
            deg = 1;
    }
    glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Bed Room 1607037");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(animate);
    glutReshapeFunc(resize);

    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);

    printf("\t********** FUNCTIONS AND CORRESPONDING KEYS **********\n \tFOR LEFT ROTATION, PRESS j \n \tFOR RIGHT ROTATION, PRESS l\n ");
    printf("\tFOR UP DIRECTION, PRESS I \n");
    printf("\tFOR DOWN DIRECTION, PRESS K \n");
    printf("\tFOR ZOOM IN, PRESS z \n");
    printf("\tFOR ZOOM OUT, PRESS x \n");
    printf("\tFOR FAN OFF, PRESS p \n");
    printf("\tFOR FAN ON, PRESS o \n");
    printf("\tFOR LIGHT1(Point Light) ON/OFF, TOGGLE 1 \n");
    printf("\tFOR LIGHT2 (Point Light) ON/OFF, TOGGLE 2 \n");
    printf("\tFOR LIGHT3 (Spot Light) ON/OFF, TOGGLE 3 \n");
    printf("\tFOR AMBIENT ON/OFF, TOGGLE a \n");
    printf("\tFOR SPECULAR ON/OFF, TOGGLE s \n");
    printf("\tFOR DIFFUSE ON/OFF, TOGGLE d \n");
    printf("\tTO QUIT, PRESS q \n");
    glutMainLoop();

    return EXIT_SUCCESS;
}
