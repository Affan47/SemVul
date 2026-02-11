adpcm_state_save_base_store (void)
{
	int i;
	struct ADPCMVoice *voice;

	for (i=0; i<num_voices; i++)
	{
		voice = &adpcm[i];
		voice_base_offset[i] = voice->base - voice->region_base;
	}
}
