ApplyAmp_adjust(SpectFrame *sp, peak_t *peaks)
{
	int  ix;
	int  y;

	memcpy(peaks,sp->peaks,sizeof(*peaks)*N_PEAKS);

	for(ix=0; ix<N_PEAKS; ix++)
	{
		y = peaks[ix].pkheight * sp->amp_adjust * amplitude;
		peaks[ix].pkheight = y / 10000;
	}
}
