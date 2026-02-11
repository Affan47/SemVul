x_read_resources(void) {
	XrmDatabase xdb;
	char* xrm;
	char* datatype[20];
	XrmValue xvalue;

	XrmInitialize();
	xrm = XResourceManagerString(dzen.dpy);
	if( xrm != NULL ) {
		xdb = XrmGetStringDatabase(xrm);
		if( XrmGetResource(xdb, "dzen2.font", "*", datatype, &xvalue) == True )
			dzen.fnt = estrdup(xvalue.addr);
		if( XrmGetResource(xdb, "dzen2.foreground", "*", datatype, &xvalue) == True )
			dzen.fg  = estrdup(xvalue.addr);
		if( XrmGetResource(xdb, "dzen2.background", "*", datatype, &xvalue) == True )
			dzen.bg  = estrdup(xvalue.addr);
		if( XrmGetResource(xdb, "dzen2.titlename", "*", datatype, &xvalue) == True )
			dzen.title_win.name  = estrdup(xvalue.addr);
		if( XrmGetResource(xdb, "dzen2.slavename", "*", datatype, &xvalue) == True )
			dzen.slave_win.name  = estrdup(xvalue.addr);
		XrmDestroyDatabase(xdb);
	}
}
