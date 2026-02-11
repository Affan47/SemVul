GXDrawSetWindowBorder(GWindow w,int width,Color col) {
    GXWindow gw = (GXWindow) w;

    if ( width>=0 )
	XSetWindowBorderWidth(gw->display->display,gw->w,width);
    if ( col!=COLOR_DEFAULT )
	XSetWindowBorder(gw->display->display,gw->w,
		_GXDraw_GetScreenPixel(gw->display,col));
}
