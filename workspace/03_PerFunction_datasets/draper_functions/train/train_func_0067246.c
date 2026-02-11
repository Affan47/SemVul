HandleShapeNotify (void)
{
    XShapeEvent	    *sev = (XShapeEvent *) &Event;

    if (Tmp_win == NULL)
	return;
    if (sev->kind != ShapeBounding)
	return;
    if (!Tmp_win->wShaped && sev->shaped) {
	XShapeCombineMask (dpy, Tmp_win->frame, ShapeClip, 0, 0, None,
			   ShapeSet);
    }
    Tmp_win->wShaped = sev->shaped;
    SetFrameShape (Tmp_win);
}
