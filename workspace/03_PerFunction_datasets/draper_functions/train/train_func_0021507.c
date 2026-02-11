do_rng_fips_test_loop( void )
{
	int j;
	int fips_result;
	struct timeval start, stop, statdump, now;
	unsigned long int statruns, runs;

	runs = statruns = 0;
	gettimeofday(&statdump, 0);
	while (!gotsigterm) {
		gettimeofday(&start, 0);
		if (xread(rng_buffer, sizeof(rng_buffer))) return;
		gettimeofday(&stop, 0);
		update_usectimer_stat(&rng_stats.source_blockfill,
				&start, &stop);

		gettimeofday(&start, 0);
		fips_result = fips_run_rng_test(&fipsctx, &rng_buffer);
		gettimeofday (&stop, 0);
		update_usectimer_stat(&rng_stats.fips_blockfill,
				&start, &stop);

		if (fips_result) {
			rng_stats.bad_fips_blocks++;
			for (j = 0; j < N_FIPS_TESTS; j++)
				if (fips_result & fips_test_mask[j])
					rng_stats.fips_failures[j]++;
		} else {
			rng_stats.good_fips_blocks++;
			if (arguments->pipemode) {
				gettimeofday(&start, 0);
				if (xwrite(rng_buffer, sizeof(rng_buffer)))
					return;
				gettimeofday (&stop, 0);
				update_usectimer_stat(
					&rng_stats.sink_blockfill,
					&start, &stop);
			}
		}

		if (arguments->blockcount &&
		    (++runs >= arguments->blockcount)) break;

		gettimeofday(&now, 0);
		if ((arguments->blockstats &&
		     (++statruns >= arguments->blockstats)) ||
		    (arguments->timedstats &&
		     (elapsed_time(&statdump, &now) > arguments->timedstats))) {
			dump_rng_stats();
			gettimeofday(&statdump, 0);
			statruns = 0;
		}
	}
}
