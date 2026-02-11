draw_worm (ModeInfo * mi)
{
	Display    *display = MI_DISPLAY(mi);
	Window      window = MI_WINDOW(mi);
	GC          gc = MI_GC(mi);
	wormstruct *wp = &worms[MI_SCREEN(mi)];
	unsigned long wcolor;
	int         i;

	(void) memset((char *) wp->size, 0, wp->nc * sizeof (int));

	for (i = 0; i < wp->nw; i++) {
		if (MI_NPIXELS(mi) > 2) {
			wcolor = (i + wp->chromo) % wp->nc;

			worm_doit(mi, i, wcolor);
		} else
			worm_doit(mi, i, (unsigned long) 0);
	}

	if (MI_WIN_IS_USE3D(mi)) {
		if (MI_WIN_IS_INSTALL(mi))
			XSetFunction(display, gc, GXor);
		XSetForeground(display, gc, MI_RIGHT_COLOR(mi));
		XFillRectangles(display, window, gc, &(wp->rects[0]), wp->size[0]);

		XSetForeground(display, gc, MI_LEFT_COLOR(mi));
		XFillRectangles(display, window, gc, &(wp->rects[wp->maxsize]), wp->size[1]);
		if (MI_WIN_IS_INSTALL(mi))
			XSetFunction(display, gc, GXcopy);
	} else if (MI_NPIXELS(mi) > 2) {
		for (i = 0; i < wp->nc; i++) {
			XSetForeground(display, gc, MI_PIXEL(mi, i));
			XFillRectangles(display, window, gc, &(wp->rects[i * wp->maxsize]), wp->size[i]);
		}
	} else {
		XSetForeground(display, gc, MI_WIN_WHITE_PIXEL(mi));
		XFillRectangles(display, window, gc,
				&(wp->rects[0]), wp->size[0]);
	}

	if (++wp->chromo == (unsigned long) wp->nc)
		wp->chromo = 0;
}
