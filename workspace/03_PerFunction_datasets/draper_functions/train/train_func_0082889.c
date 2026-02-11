SetPitch2(voice_t *voice, int pitch1, int pitch2, int *pitch_base, int *pitch_range)
{
	int x;
	int base;
	int range;
	int pitch_value;

	if(pitch1 > pitch2)
	{
		x = pitch1;
		pitch1 = pitch2;
		pitch2 = x;
	}

	if((pitch_value = embedded_value[EMBED_P]) > MAX_PITCH_VALUE)
		pitch_value = MAX_PITCH_VALUE;
	pitch_value -= embedded_value[EMBED_T];
	if(pitch_value < 0)
		pitch_value = 0;

	base = (voice->pitch_base * pitch_adjust_tab[pitch_value])/128;
	range =  (voice->pitch_range * embedded_value[EMBED_R])/50;


	base -= (range - voice->pitch_range)*18;

	*pitch_base = base + (pitch1 * range)/2;
	*pitch_range = base + (pitch2 * range)/2 - *pitch_base;
}
