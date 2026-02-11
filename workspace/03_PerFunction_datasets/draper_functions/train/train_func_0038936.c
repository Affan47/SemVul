UpdateBackgroundTransparency(
	Display *dpy, Window win, int width, int height,
	colorset_t *colorset, unsigned int depth, GC gc, Bool clear_area)
{
	if (!CSETS_IS_TRANSPARENT(colorset))
	{
		return False;
	}
	else if (!CSETS_IS_TRANSPARENT_PR_PURE(colorset))
	{
		SetWindowBackgroundWithOffset(
			dpy, win, 0, 0, width, height, colorset, depth, gc,
			True);
	}
	else
	{
		XClearArea(dpy, win, 0,0,0,0, clear_area);
	}

	return True;
}
