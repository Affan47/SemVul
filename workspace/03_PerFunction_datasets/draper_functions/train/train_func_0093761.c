ScrollPixmap(
	Display *dpy, Pixmap p, GC gc, int x_off, int y_off, int width,
	int height, unsigned int depth)
{
	GC tgc;
	XGCValues xgcv;
	Pixmap p2;

	if (p == None || p == ParentRelative || (x_off == 0 && y_off == 0))
	{
		return p;
	}
	tgc = fvwmlib_XCreateGC(dpy, p, 0, &xgcv);
	if (tgc == None)
	{
		return p;
	}
	XCopyGC(dpy, gc, GCFunction | GCPlaneMask| GCSubwindowMode |
		GCClipXOrigin | GCClipYOrigin | GCClipMask, tgc);
	xgcv.tile = p;
	xgcv.ts_x_origin = x_off;
	xgcv.ts_y_origin = y_off;
	xgcv.fill_style = FillTiled;
	XChangeGC(
		dpy, tgc, GCTile | GCTileStipXOrigin | GCTileStipYOrigin |
		GCFillStyle, &xgcv);
	p2 = XCreatePixmap(dpy, p, width, height, depth);
	if (p2 == None)
	{
		return p;
	}
	XFillRectangle(dpy, p2, tgc, 0, 0, width, height);
	XFreeGC(dpy, tgc);

	return p2;
}
