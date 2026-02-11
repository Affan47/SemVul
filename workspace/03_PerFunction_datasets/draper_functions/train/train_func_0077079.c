change_rate_less(RATE_data *RT, SAMPLE *Buff, int rate, int NumSamples, int channels)
{
	int samp = 0;
	int n = 0, i = 0;


	for (samp = 0; samp < NumSamples; samp += channels)
	{


		if (n==0)
		{
			RT->rBuff1[i] = Buff[samp];
			if(channels > 1)
				RT->rBuff2[i] = Buff[samp + 1];

			i++;
		}
		if(++n >= rate) n=0;
	}
	RT->numsamples = i;
}
