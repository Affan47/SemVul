plP_draphy_poly(PLINT *x, PLINT *y, PLINT n)
{
    PLINT i, j, ib, ilim;

    for (ib = 0; ib < n; ib += PL_MAXPOLY - 1) {
	ilim = MIN(PL_MAXPOLY, n - ib);

	for (i = 0; i < ilim; i++) {
	    j = ib + i;
	    xline[i] = x[j];
	    yline[i] = y[j];
	}
	pllclp(xline, yline, ilim);
    }
}
