interv(double *xt, int *lxt, double *x, int *left, int *mflag)
{
	static int ilo = 1;
	static int istep, middle, ihi;

	--xt;


	ihi = ilo + 1;
	if (ihi < *lxt) {
		goto L20;
	}
	if (*x >= xt[*lxt]) {
		goto L110;
	}
	if (*lxt <= 1) {
		goto L90;
	}
	ilo = *lxt - 1;
	ihi = *lxt;

 L20:
	if (*x >= xt[ihi]) {
		goto L40;
	}
	if (*x >= xt[ilo]) {
		goto L100;
	}


	istep = 1;
 L31:
	ihi = ilo;
	ilo = ihi - istep;
	if (ilo <= 1) {
		goto L35;
	}
	if (*x >= xt[ilo]) {
		goto L50;
	}
	istep <<= 1;
	goto L31;
 L35:
	ilo = 1;
	if (*x < xt[1]) {
		goto L90;
	}
	goto L50;

 L40:
	istep = 1;
 L41:
	ilo = ihi;
	ihi = ilo + istep;
	if (ihi >= *lxt) {
		goto L45;
	}
	if (*x < xt[ihi]) {
		goto L50;
	}
	istep <<= 1;
	goto L41;
 L45:
	if (*x >= xt[*lxt]) {
		goto L110;
	}
	ihi = *lxt;


 L50:
	middle = (ilo + ihi) / 2;
	if (middle == ilo) {
		goto L100;
	}

	if (*x < xt[middle]) {
		goto L53;
	}
	ilo = middle;
	goto L50;
 L53:
	ihi = middle;
	goto L50;

 L90:
	*mflag = -1;
	*left = 1;
	return 0;
 L100:
	*mflag = 0;
	*left = ilo;
	return 0;
 L110:
	*mflag = 1;
	if (*x == xt[*lxt]) {
		*mflag = 0;
	}
	*left = *lxt;
 L111:
	if (*left == 1) {
		return 0;
	}
	--(*left);
	if (xt[*left] < xt[*lxt]) {
		return 0;
	}
	goto L111;
}
