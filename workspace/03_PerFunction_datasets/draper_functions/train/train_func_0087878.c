ADPCM_setvol(int num, int vol)
{
	struct ADPCMVoice *voice = &adpcm[num+msm_voices];


	if (Machine->sample_rate == 0)
		return;


	if ((num+msm_voices) >= num_voices)
	{
		logerror("error: ADPCM_setvol() called with channel = %d, but only %d channels allocated\n", num, num_voices);
		return;
	}


	stream_update(voice->stream, 0);
	voice->volume = vol;
}
