all_pass (delay_data *AP, SAMPLE *Buff, int NumSamples, int channels, float gain)
{
	int samp = 0;
	float inv_gain = 1.0 / gain;

	for(samp = 0; samp < NumSamples; samp += channels)
	{
		AP->delayBuff1[AP->delayIndex] = Buff[samp] +
			(gain * AP->delayBuff1[AP->delayIndex]);
		Buff[samp] = ((AP->delayBuff1[AP->delayIndex] * (1 - gain*gain)) -
			Buff[samp]) * inv_gain;
		if(channels > 1)
		{
			AP->delayBuff2[AP->delayIndex] = Buff[samp+1] +
				(gain * AP->delayBuff2[AP->delayIndex]);
			Buff[samp+1] = ((AP->delayBuff2[AP->delayIndex] * (1 - gain*gain)) -
				Buff[samp+1]) * inv_gain;
		}

		if(++(AP->delayIndex) >= AP->buff_size) AP->delayIndex=0;
	}
}
