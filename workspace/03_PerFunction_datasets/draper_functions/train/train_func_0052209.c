init_thornbird (ModeInfo * mi)
{
	thornbirdstruct *hp;

	if (thornbirds == NULL) {
		if ((thornbirds =
		     (thornbirdstruct *) calloc(MI_NUM_SCREENS(mi),
					  sizeof (thornbirdstruct))) == NULL)
			return;
	}
	hp = &thornbirds[MI_SCREEN(mi)];


	hp->maxx = MI_WIDTH(mi);
	hp->maxy = MI_HEIGHT(mi);

	hp->b = 0.1;
	hp->i = hp->j = 0.1;

	hp->pix = 0;
	hp->inc = 0;

	hp->nbuffers = MI_CYCLES(mi);

	if (hp->pointBuffer == NULL)
		if ((hp->pointBuffer = (XPoint **) calloc(MI_CYCLES(mi),
				sizeof (XPoint *))) == NULL) {
			free_thornbird(hp);
			return;
		}

	if (hp->pointBuffer[0] == NULL)
		if ((hp->pointBuffer[0] = (XPoint *) malloc(MI_COUNT(mi) *
				sizeof (XPoint))) == NULL) {
			free_thornbird(hp);
			return;
		}


	hp->liss.f1 = LRAND() % 5000;
	hp->liss.f2 = LRAND() % 2000;


	hp->tumble.theta = 0;
	hp->tumble.phi = 0;
	hp->tumble.dtheta = balance_rand(0.001);
	hp->tumble.dphi = balance_rand(0.005);


	MI_CLEARWINDOW(mi);

	hp->count = 0;
}
