redrawGL2PS()
{
	GLdouble m[4][4];
	GtkWidget *widget = GLArea;
	if(!GTK_IS_WIDGET(widget)) return TRUE;
	if(!GTK_WIDGET_REALIZED(widget)) return TRUE;

    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	addFog();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	set_background_color();

	mYPerspective(45,(GLdouble)widget->allocation.width/(GLdouble)widget->allocation.height,1,100);
    	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(optcol==-1) drawChecker();

    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	if(perspective)
		mYPerspective(Zoom,(GLdouble)widget->allocation.width/(GLdouble)widget->allocation.height,zNear,zFar);
	else
	{
	  	gdouble fw = (GLdouble)widget->allocation.width/(GLdouble)widget->allocation.height;
	  	gdouble fh = 1.0;
		glOrtho(-fw,fw,-fh,fh,-1,1);
	}

    	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(perspective)
		glTranslatef(Trans[0],Trans[1],Trans[2]);
	else
	{
		 glTranslatef(Trans[0]/10,Trans[1]/10,0);
		 glScalef(1/Zoom*2,1/Zoom*2,1/Zoom*2);
	}
	SetLight();

	build_rotmatrix(m,Quat);
	glMultMatrixd(&m[0][0]);

	redrawGeometry();
	redrawSurfaces();
	redrawCell();
	redrawContours();
	redrawPlanesMapped();
	if(get_show_symbols() || get_show_numbers() || get_show_charges()) showLabelSymbolsNumbersCharges();
	if(get_show_dipole()) showLabelDipole();
	if(get_show_distances()) showLabelDistances();
	if(get_show_axes()) showLabelAxes();
	if(get_show_axes()) showLabelPrincipalAxes();
	showLabelTitle(GLArea->allocation.width,GLArea->allocation.height);


	glFlush();

	return TRUE;
}
