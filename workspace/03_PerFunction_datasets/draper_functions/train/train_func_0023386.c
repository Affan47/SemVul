moveto_lineto_radec(plot_args_t* pargs, double ra, double dec, anbool move) {
	double x,y;
	if (!plotstuff_radec2xy(pargs, ra, dec, &x, &y)) {
		ERROR("Failed to convert RA,Dec (%g,%g) to pixel position in plot_text_radec\n", ra, dec);
		return -1;
	}
	assert(pargs->cairo);
	(move ? plotstuff_move_to : plotstuff_line_to)(pargs, x, y);
	return 0;
}
