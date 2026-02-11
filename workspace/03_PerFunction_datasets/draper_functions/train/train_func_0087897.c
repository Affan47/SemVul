fft( FFT_Tables *fft_tables, double *xr, double *xi, int logm)
{
	if (logm > MAXLOGM)
	{
		fprintf(stderr, "fft size too big\n");
		exit(1);
	}

	if (logm < 1)
	{

		return;
	}

	check_tables( fft_tables, logm);

	reorder( fft_tables, xr, logm);
	reorder( fft_tables, xi, logm);

	fft_proc( xr, xi, fft_tables->costbl[logm], fft_tables->negsintbl[logm], 1 << logm );
}
