conv_rspl_out(
	void *pp,
	double *out,
	double *in
) {
	xfit *p    = (xfit *)pp;
	double tt[3];


	xfit_outcurves(p, tt, out);

	if (p->flags & XFIT_OUT_LAB) {
		icmLab2XYZ(&icmD50, tt, tt);
		icmMulBy3x3(out, p->cmat, tt);
		icmXYZ2Lab(&icmD50, out, out);

	} else {
		icmMulBy3x3(out, p->cmat, tt);
	}


	xfit_invoutcurves(p, out, out);
}
