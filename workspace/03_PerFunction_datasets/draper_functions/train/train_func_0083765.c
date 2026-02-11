loop_model_zero (LOOP_MODEL *lmod, int started)
{
    int i, bnc = 4 * lmod->nc;

#if LOOP_DEBUG
    fprintf(stderr, "loop_model_zero: %p\n", (void *) lmod);
#endif

    for (i=0; i<bnc; i++) {
	if (started) {
	    mpf_set_d(lmod->bigarray[i], 0.0);
	} else {
	    mpf_init(lmod->bigarray[i]);
	}
    }

    for (i=0; i<lmod->nc; i++) {
	lmod->cbak[i] = lmod->sbak[i] = NADBL;
	lmod->cdiff[i] = lmod->sdiff[i] = 0;
    }

    lmod->n = 0;
}
