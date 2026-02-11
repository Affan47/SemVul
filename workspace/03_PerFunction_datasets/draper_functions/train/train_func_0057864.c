init_filter()
{
	flen2 = flen >> 1;
	fft			= new g_fft<double>(flen);

	filter		= new cmplx[flen];
	timedata	= new cmplx[flen];
	freqdata	= new cmplx[flen];
	output		= new cmplx[flen];
	ovlbuf		= new cmplx[flen2];
	ht			= new cmplx[flen];

	memset(filter, 0, flen * sizeof(cmplx));
	memset(timedata, 0, flen * sizeof(cmplx));
	memset(freqdata, 0, flen * sizeof(cmplx));
	memset(output, 0, flen * sizeof(cmplx));
	memset(ovlbuf, 0, flen2 * sizeof(cmplx));
	memset(ht, 0, flen * sizeof(cmplx));

	inptr = 0;
}
