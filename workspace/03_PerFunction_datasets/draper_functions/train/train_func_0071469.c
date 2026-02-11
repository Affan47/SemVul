gra_sphere(double x,double y,double z,double f,double r)
{
    int Division = 4*GRA_SphereQuality;
    int i,j;

    if ( !GRA_SphereInitDone ) gra_sphere_quality( GRA_SphereQuality );

    glPushMatrix();

    glTranslatef(x,y,z);
    glScalef(r,r,r);

    for( i=0; i<Division/2; i++ )
    {
        glBegin(GL_QUAD_STRIP);
            x = GRA_CosB[i];
            y = 0.0;
            z = GRA_SinB[i];

            glTexCoord1d( f );
            glNormal3f(-x,-y,-z);
            glVertex3f(x,y,z);

            x = GRA_CosB[i+1];
            y = 0.0;
            z = GRA_SinB[i+1];

            glTexCoord1d( f );
            glNormal3d( -x,-y,-z );
            glVertex3d( x,y,z );

            for( j=1; j<=Division; j++ )
            {
                x = GRA_CosA[j]*GRA_CosB[i];
                y = GRA_SinA[j]*GRA_CosB[i];
                z = GRA_SinB[i];

                glTexCoord1d( f );
                glNormal3d( -x,-y,-z );
                glVertex3d( x,y,z );

                x = GRA_CosA[j]*GRA_CosB[i+1];
                y = GRA_SinA[j]*GRA_CosB[i+1];
                z = GRA_SinB[i+1];

                glTexCoord1d( f );
                glNormal3d( -x,-y,-z );
                glVertex3d( x,y,z );
            }
        glEnd();
    }

    glPopMatrix();

    glNormal3d( 0.0,0.0,1.0 );
}
