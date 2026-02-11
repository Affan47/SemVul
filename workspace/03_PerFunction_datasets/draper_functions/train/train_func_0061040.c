setup_balloon_gc(int i, PagerWindow *t)
{
	XGCValues xgcv;
	unsigned long valuemask;

	valuemask = GCForeground;
	if (Desks[i].ballooncolorset < 0)
	{
		xgcv.foreground =
			(!BalloonFore) ? fore_pix : GetColor(BalloonFore);
		if (BalloonFore == NULL)
		{
			XSetForeground(dpy, Scr.balloon_gc, t->text);
		}
	}
	else
	{
		xgcv.foreground = Colorset[Desks[i].ballooncolorset].fg;
	}
	if (Desks[i].balloon.Ffont->font != NULL)
	{
		xgcv.font = Desks[i].balloon.Ffont->font->fid;
		valuemask |= GCFont;
	}
	XChangeGC(dpy, Scr.balloon_gc, valuemask, &xgcv);

	return;
}
