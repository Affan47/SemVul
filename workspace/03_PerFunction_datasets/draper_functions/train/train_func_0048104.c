drawdata(short *data, int len, int replace, int xm)
{
	int cnt;
        GC gc;
        XGCValues gcv;
        XWindowAttributes winattrs;

        if (!display || !pixmap)
                return;
        XGetWindowAttributes(display, window, &winattrs);
	gcv.line_width = 1;
        gcv.line_style = LineSolid;
        gc = XCreateGC(display, pixmap, GCLineWidth | GCLineStyle, &gcv);
        XSetState(display, gc, col_background, col_background, GXcopy,
		  AllPlanes);
	if (replace)
		XFillRectangle(display, pixmap, gc, 0, 0,
			       winattrs.width, winattrs.height);
	else
		XCopyArea(display, window, pixmap, gr_context, 0, 0,
			  winattrs.width, winattrs.height, 0, 0);
        XSetForeground(display, gc, col_trace);
	for (cnt = 0; cnt < len-1; cnt++)
		XDrawLine(display, pixmap, gc, XCOORD(cnt), YCOORD(data[cnt]),
			  XCOORD(cnt+1), YCOORD(data[cnt+1]));
        XSetForeground(display, gc, col_zeroline);
	XDrawLine(display, pixmap, gc, 0, YCOORD(0), winattrs.width,
		  YCOORD(0));
	XCopyArea(display, pixmap, window, gr_context, 0, 0, winattrs.width,
                  winattrs.height, 0, 0);
        XFreeGC(display, gc);
	XSync(display, 0);
}
