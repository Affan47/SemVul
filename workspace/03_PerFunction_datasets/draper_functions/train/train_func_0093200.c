fft_initialize( FFT_Tables *fft_tables )
{
	int i;
	fft_tables->costbl		= AllocMemory( (MAXLOGM+1) * sizeof( fft_tables->costbl[0] ) );
	fft_tables->negsintbl	= AllocMemory( (MAXLOGM+1) * sizeof( fft_tables->negsintbl[0] ) );
	fft_tables->reordertbl	= AllocMemory( (MAXLOGM+1) * sizeof( fft_tables->reordertbl[0] ) );

	for( i = 0; i< MAXLOGM+1; i++ )
	{
		fft_tables->costbl[i]		= NULL;
		fft_tables->negsintbl[i]	= NULL;
		fft_tables->reordertbl[i]	= NULL;
	}
}
