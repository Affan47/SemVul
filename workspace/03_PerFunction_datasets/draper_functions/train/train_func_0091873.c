sample_playing(int channel)
{
	if (Machine->sample_rate == 0) return 0;
	if (channel >= numchannels)
	{
		logerror("error: sample_playing() called with channel = %d, but only %d channels allocated\n",channel,numchannels);
		return 0;
	}

	return mixer_is_sample_playing(channel + firstchannel);
}
