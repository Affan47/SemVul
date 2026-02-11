draw_grav(ModeInfo * mi)
{
	Display    *display = MI_DISPLAY(mi);
	Window      window = MI_WINDOW(mi);
	GC          gc = MI_GC(mi);
	register unsigned char ball;
	gravstruct *gp;

	if (gravs == NULL)
			return;
	gp = &gravs[MI_SCREEN(mi)];
	if (gp->planets == NULL)
		return;

	MI_IS_DRAWN(mi) = True;

	XSetForeground(display, gc, MI_BLACK_PIXEL(mi));
	XDrawArc(display, window, gc,
		 gp->width / 2 - gp->sr / 2, gp->height / 2 - gp->sr / 2, gp->sr, gp->sr,
		 0, 23040);


	switch (NRAND(4)) {
		case 0:
			if (gp->sr < (int) STARRADIUS)
				gp->sr++;
			break;
		case 1:
			if (gp->sr > 2)
				gp->sr--;
	}


	XSetForeground(display, gc, gp->starcolor);
	XDrawArc(display, window, gc,
		 gp->width / 2 - gp->sr / 2, gp->height / 2 - gp->sr / 2, gp->sr, gp->sr,
		 0, 23040);

	for (ball = 0; ball < (unsigned char) gp->nplanets; ball++)
		draw_planet(mi, &gp->planets[ball]);
}
