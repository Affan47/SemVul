startover(ModeInfo * mi)
{
	int         j;
	sierpinskistruct *sp = &tris[MI_SCREEN(mi)];

	if (MI_NPIXELS(mi) > 2) {
		if (sp->corners == 3) {
			sp->colors[0] = (NRAND(MI_NPIXELS(mi)));
			sp->colors[1] = (sp->colors[0] + MI_NPIXELS(mi) / 7 +
			 NRAND(2 * MI_NPIXELS(mi) / 7 + 1)) % MI_NPIXELS(mi);
			sp->colors[2] = (sp->colors[0] + 4 * MI_NPIXELS(mi) / 7 +
			 NRAND(2 * MI_NPIXELS(mi) / 7 + 1)) % MI_NPIXELS(mi);
		} else if (sp->corners == 4) {
			sp->colors[0] = (NRAND(MI_NPIXELS(mi)));
			sp->colors[1] = (sp->colors[0] + MI_NPIXELS(mi) / 7 +
			     NRAND(MI_NPIXELS(mi) / 7 + 1)) % MI_NPIXELS(mi);
			sp->colors[2] = (sp->colors[0] + 3 * MI_NPIXELS(mi) / 7 +
			     NRAND(MI_NPIXELS(mi) / 7 + 1)) % MI_NPIXELS(mi);
			sp->colors[3] = (sp->colors[0] + 5 * MI_NPIXELS(mi) / 7 +
			     NRAND(MI_NPIXELS(mi) / 7 + 1)) % MI_NPIXELS(mi);
		} else {
			(void) fprintf(stderr, "colors not set for %d corners\n", sp->corners);
		}
	}
	for (j = 0; j < sp->corners; j++) {
		sp->vertex[j].x = NRAND(sp->width);
		sp->vertex[j].y = NRAND(sp->height);
	}
	sp->px = NRAND(sp->width);
	sp->py = NRAND(sp->height);
	sp->time = 0;

	MI_CLEARWINDOW(mi);
}
