init_grav(ModeInfo * mi)
{
	Display    *display = MI_DISPLAY(mi);
	GC          gc = MI_GC(mi);
	unsigned char ball;
	gravstruct *gp;

	if (gravs == NULL) {
		if ((gravs = (gravstruct *) calloc(MI_NUM_SCREENS(mi),
					       sizeof (gravstruct))) == NULL)
			return;
	}
	gp = &gravs[MI_SCREEN(mi)];

	gp->width = MI_WIDTH(mi);
	gp->height = MI_HEIGHT(mi);

	gp->sr = STARRADIUS;

	gp->nplanets = MI_COUNT(mi);
	if (gp->nplanets < 0) {
		if (gp->planets) {
			(void) free((void *) gp->planets);
			gp->planets = (planetstruct *) NULL;
		}
		gp->nplanets = NRAND(-gp->nplanets) + 1;
	}
	if (gp->planets == NULL) {
		if ((gp->planets = (planetstruct *) calloc(gp->nplanets,
				sizeof (planetstruct))) == NULL)
			return;
	}

	MI_CLEARWINDOW(mi);

	if (MI_NPIXELS(mi) > 2)
		gp->starcolor = MI_PIXEL(mi, NRAND(MI_NPIXELS(mi)));
	else
		gp->starcolor = MI_WHITE_PIXEL(mi);
	for (ball = 0; ball < (unsigned char) gp->nplanets; ball++)
		init_planet(mi, &gp->planets[ball]);


	XDrawArc(display, MI_WINDOW(mi), gc,
		 gp->width / 2 - gp->sr / 2, gp->height / 2 - gp->sr / 2, gp->sr, gp->sr,
		 0, 23040);
}
