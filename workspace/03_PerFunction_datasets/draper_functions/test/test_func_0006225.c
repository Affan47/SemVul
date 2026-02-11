init_vines(ModeInfo * mi)
{
	vinestruct *fp;

	if (vines == NULL) {
		if ((vines = (vinestruct *) calloc(MI_NUM_SCREENS(mi),
					     sizeof (vinestruct))) == NULL) {
			return;
		}
	}
	fp = &vines[MI_SCREEN(mi)];

	fp->i = 0;
	fp->length = 0;
	fp->iterations = 30 + NRAND(100);

#ifndef STANDALONE
	MI_CLEARWINDOW(mi);
#endif
}
