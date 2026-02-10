SeqSetEntropy(ss_type P)
{
	long	i;
	double	*freq,H;

	freq = tFreqSeqSet(P);
	for(H=0.0,i = 1; i <= nAlpha(P->A); i++){
		if(freq[i] > 0.0) H += freq[i] * log(freq[i]);
	}
	return (-1.442695041*H);
}
