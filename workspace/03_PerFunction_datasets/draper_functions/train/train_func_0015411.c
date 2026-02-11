make_named_month_tics (const gnuplot_info *gi, double yrs,
				   PRN *prn)
{
    double t0 = gi->x[gi->t1];
    double t1 = gi->x[gi->t2];
    double x, tw = 1.0/12;
    int i, m, n = 0;
    char mname[16];
    int notfirst = 0;
    int scale = (int) (yrs * 1.5);

    if (scale == 0) {
	scale = 1;
    }

    t0 += (1.0 - (t0 - floor(t0)) * 12.0) / 12.0;
    for (x=t0; x<t1; x+=tw) n++;

    x = (t0 - floor(t0)) * 12;
    m = 1 + ((x - floor(x) > .8)? ceil(x) : floor(x));
    if (m > 12) m -= 12;

    pputs(prn, "set xtics (");
    x = t0;

    gretl_push_c_numeric_locale();

    for (i=0; i<n; i++) {
	if (m == 1) {
	    if (notfirst) {
		pputs(prn, ", ");
	    }
	    pprintf(prn, "\"%4.0f\" %.10g", x, x);
	    notfirst = 1;
	} else if ((scale == 1) || (m % scale == 1)) {
	    graph_month_name(mname, m);
	    if (notfirst) {
		pputs(prn, ", ");
	    }
	    pprintf(prn, "\"%s\" %.10g", mname, x);
	    notfirst = 1;
	}
	m++;
	x += tw;
	if (m > 12) m -= 12;
    }

    gretl_pop_c_numeric_locale();

    pputs(prn, ")\n");
}
