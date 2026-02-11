drawASticker (float size, int color, bool blinking,
			       int faceNormal[], float faceCentre [])
{
    float lenA = 0.5   * size;
    float bevel = bevelAmount * lenA;
    float lenB = lenA - bevel;

    float p[nAxes];
    float normal[nAxes];

    int axis1 = 0, axis2 = 1;

    float mColor [3];

    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
    glPushMatrix();


    if (blinking) {
	LOOP (i, 3) {
	    mColor [i] = blinkIntensity * colors [color] [i];
	}
	glColor3fv (mColor);
    }
    else {
	glColor3fv (colors [color]);
    }


    glTranslatef ((GLfloat) faceCentre[X],
                  (GLfloat) faceCentre[Y],
                  (GLfloat) faceCentre[Z]);

    LOOP (axis, 3) {
	normal [axis] = 0.0;
	if (faceNormal [axis] != 0) {

	    normal [axis] = (float) faceNormal [axis];


	    p [axis] = 0.01 * size * normal [axis];


	    if (faceNormal [axis] > 0) {
		axis1 = (axis + 1) % 3;
		axis2 = (axis + 2) % 3;
	    }
	    else {
		axis2 = (axis + 1) % 3;
		axis1 = (axis + 2) % 3;
	    }
	}
    }

    glBegin(GL_QUADS);
    glNormal3fv (normal);

    p [axis1] = + lenB;
    p [axis2] = + lenB;
    glVertex3fv (p);
    p [axis1] = - lenB;
    glVertex3fv (p);
    p [axis2] = - lenB;
    glVertex3fv (p);
    p [axis1] = + lenB;
    glVertex3fv (p);

    glEnd();

    glPopAttrib();
    glPopMatrix();
    checkGLError();
}
