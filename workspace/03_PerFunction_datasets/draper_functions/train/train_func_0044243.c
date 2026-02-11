X86_MonoFromStereo(int *pMixBuf, UINT nSamples)
{
	UINT j;
	for(UINT i = 0; i < nSamples; i++)
	{
		j = i << 1;
		pMixBuf[i] = (pMixBuf[j] + pMixBuf[j + 1]) >> 1;
	}
}
