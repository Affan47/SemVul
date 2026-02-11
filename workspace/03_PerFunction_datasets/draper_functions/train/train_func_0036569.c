drawcell(ModeInfo * mi, int col, int row, int state)
{
	loopstruct *lp = &loops[MI_SCREEN(mi)];
	XGCValues   gcv;
	GC          gc;

	if (MI_NPIXELS(mi) >= COLORS) {
		gc = MI_GC(mi);
		XSetForeground(MI_DISPLAY(mi), gc, lp->colors[state]);
	} else {
#ifdef DO_STIPPLE
		gcv.stipple = lp->pixmaps[state];
#endif
		gcv.foreground = MI_WHITE_PIXEL(mi);
		gcv.background = MI_BLACK_PIXEL(mi);
		XChangeGC(MI_DISPLAY(mi), lp->stippledGC,
#ifdef DO_STIPPLE
			  GCStipple |
#endif
                          GCForeground | GCBackground, &gcv);
		gc = lp->stippledGC;
	}
	fillcell(mi, gc, col, row);
}
