calculate_adjustment(const double factor,
		     const time_t last_time,
		     const double not_adjusted,
		     const time_t systime, int *adjustment_p, double *retro_p)
{
	double exact_adjustment;

	exact_adjustment =
	    ((double)(systime - last_time)) * factor / (24 * 60 * 60)
	    + not_adjusted;
	*adjustment_p = FLOOR(exact_adjustment);

	*retro_p = exact_adjustment - (double)*adjustment_p;
	if (debug) {
		printf(_("Time since last adjustment is %d seconds\n"),
		       (int)(systime - last_time));
		printf(_("Need to insert %d seconds and refer time back "
			 "%.6f seconds ago\n"), *adjustment_p, *retro_p);
	}
}
