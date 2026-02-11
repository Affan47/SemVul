S_TransferStereo16 (unsigned int *pbuf, int endtime)
{
	int		lpos, lpaintedtime;

	snd_p = (int *) paintbuffer;
	lpaintedtime = paintedtime;

	while (lpaintedtime < endtime)
	{

		lpos = lpaintedtime & ((dma.samples>>1)-1);

		snd_out = (int16 *) pbuf + (lpos<<1);

		snd_linear_count = (dma.samples>>1) - lpos;
		if (lpaintedtime + snd_linear_count > endtime)
			snd_linear_count = endtime - lpaintedtime;

		snd_linear_count <<= 1;


		if( s_swapstereo->integer )
			S_WriteSwappedLinearBlastStereo16 ();
		else
			S_WriteLinearBlastStereo16 ();

		snd_p += snd_linear_count;
		lpaintedtime += (snd_linear_count>>1);

#ifdef AVI_EXPORT
		Movie_TransferStereo16 ();
#endif
	}
}
