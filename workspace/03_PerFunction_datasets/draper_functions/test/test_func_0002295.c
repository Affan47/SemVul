gnuplot_too_old (void)
{
    static double gpv;

    if (gpv == 0.0) {
	gpv = gnuplot_version();
    }

    if (gpv < 4.4) {
	gretl_errmsg_set("Gnuplot is too old: must be >= version 4.4.0");
	return 1;
    } else {
	return 0;
    }
}
