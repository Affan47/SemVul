icx_spectrum_locus(double xyz[3], double wl, icxObserverType obType) {
	xspect *sp[3];

	DBGF((DBGA,"icx_spectrum_locus got obs %d wl %f\n",obType, wl));

	if (standardObserver(sp, obType))
		return 1;

	if (wl < sp[0]->spec_wl_short)
		wl = sp[0]->spec_wl_short;
	if (wl > sp[0]->spec_wl_long)
		wl = sp[0]->spec_wl_long;

	xyz[0] = value_xspect(sp[0], wl);
	xyz[1] = value_xspect(sp[1], wl);
	xyz[2] = value_xspect(sp[2], wl);

	DBGF((DBGA,"returning %f %f %f\n", xyz[0], xyz[1], xyz[2]));

	return 0;
}
