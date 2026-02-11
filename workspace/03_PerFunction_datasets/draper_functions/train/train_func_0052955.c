_GXDraw_GetCursor( GXDisplay *gdisp, enum cursor_types ct ) {
    Display *display = gdisp->display;

    if ( ct>=ct_user )
return( ct-ct_user );
    else if ( ct==ct_default )
return( CopyFromParent );
    if ( StdCursor[ct]==0 ) {
	XColor fb[2];
	fb[0].red = COLOR_RED(gdisp->def_foreground)*0x101; fb[0].green = COLOR_GREEN(gdisp->def_foreground)*0x101; fb[0].blue = COLOR_BLUE(gdisp->def_foreground)*0x101;
	fb[1].red = COLOR_RED(gdisp->def_background)*0x101; fb[1].green = COLOR_GREEN(gdisp->def_background)*0x101; fb[1].blue = COLOR_BLUE(gdisp->def_background)*0x101;
	if ( ct==ct_invisible ) {
	    static short zeros[16]={0};
	    Pixmap temp = XCreatePixmapFromBitmapData(display,gdisp->root,
		(char *) zeros,16,16,1,0,1);
	    StdCursor[ct] = XCreatePixmapCursor(display,temp,temp,&fb[0],&fb[1],0,0);
	    XFreePixmap(display,temp);
	} else {
	    StdCursor[ct] = XCreateFontCursor(display,cursor_map[ct]);

	}
    }
return( StdCursor[ct]);
}
