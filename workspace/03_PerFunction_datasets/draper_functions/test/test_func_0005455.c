scale_icon (task *tk)
{
	int xx, yy, x, y;
	unsigned int w, h, d, bw;
	Pixmap pix, mk = None;
	XGCValues gcv;
	GC mgc = None;

	Window unused;
	XGetGeometry (dd, tk->icon, &unused, &x, &y, &w, &h, &bw, &d);
	pix = XCreatePixmap (dd, tk->win, ICONWIDTH, ICONHEIGHT, scr_depth);

	if (tk->mask != None)
	{
		mk = XCreatePixmap (dd, tk->win, ICONWIDTH, ICONHEIGHT, 1);
		gcv.subwindow_mode = IncludeInferiors;
		gcv.graphics_exposures = False;
		mgc = XCreateGC (dd, mk, GCGraphicsExposures | GCSubwindowMode, &gcv);
	}

	set_foreground (3);


	for (y = ICONHEIGHT - 1; y >= 0; y--)
	{
		yy = (y * h) / ICONHEIGHT;
		for (x = ICONWIDTH - 1; x >= 0; x--)
		{
			xx = (x * w) / ICONWIDTH;
			if (d != scr_depth)
				XCopyPlane (dd, tk->icon, pix, fore_gc, xx, yy, 1, 1, x, y, 1);
			else
				XCopyArea (dd, tk->icon, pix, fore_gc, xx, yy, 1, 1, x, y);
			if (mk != None)
				XCopyArea (dd, tk->mask, mk, mgc, xx, yy, 1, 1, x, y);
		}
	}

	if (mk != None)
	{
		XFreeGC (dd, mgc);
		tk->mask = mk;
	}

	tk->icon = pix;
}
