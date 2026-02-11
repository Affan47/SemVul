audio_wave_prepare(int wid)
{
	int w, first, last;
	if(wid < 0)
	{
		first = 0;
		last = AUDIO_MAX_WAVES - 1;
	}
	else
		first = last = wid;
	for(w = first; w <= last; ++w)
	{
		if(!wavetab[w].allocated)
			continue;
		_calc_info(w);
		_render_extension(w);
	}
}
