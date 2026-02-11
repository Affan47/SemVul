update_stars(float dt) {
    int i;

    mode_ortho();
    mode_lines();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	for (i=0; i<nstars; i++) {
		stars[i].z -= speed*dt/500;
        if (stars[i].z < 0) stars[i].z += zmax;
        if (stars[i].z > zmax) stars[i].z -= zmax;

        double x = stars[i].x/stars[i].z;
        double y = stars[i].y/stars[i].z;
        x = (x*zmax+1)/2;
        y = (y*zmax+1)/2;

        if (stars[i].z > zmax/2) glPointSize(1);
        else glPointSize(2);
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
    ortho_done();
}
