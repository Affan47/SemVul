GXDrawSetZoom(GWindow w, GRect *pos, enum gzoom_flags flags) {
    XSizeHints zoom, normal;
    Display *display = ((GXWindow) w)->display->display;
    long supplied_return;

    memset(&zoom,0,sizeof(zoom));
    if ( flags&gzf_pos ) {
	zoom.x = pos->x;
	zoom.y = pos->y;
	zoom.flags = PPosition;
    }
    if ( flags&gzf_size ) {
	zoom.width = zoom.base_width = zoom.max_width = pos->width;
	zoom.height = zoom.base_height = zoom.max_height = pos->height;
	zoom.flags |= PSize | PBaseSize | PMaxSize;
	XGetWMNormalHints(display,((GXWindow) w)->w,&normal,&supplied_return);
	normal.flags |= PMaxSize;
	normal.max_width = pos->width;
	normal.max_height = pos->height;
	XSetWMNormalHints(display,((GXWindow) w)->w,&normal);
    }
    XSetWMSizeHints(display,((GXWindow) w)->w,&zoom,XA_WM_ZOOM_HINTS);
}
