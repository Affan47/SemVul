ok_xy_count (int t1, int t2, const double *x, const double *y)
{
    int t, n = 0;

    for (t=t1; t<=t2; t++) {
	if (complete_obs(x, y, t)) {
	    n++;
	}
    }

    return n;
}
