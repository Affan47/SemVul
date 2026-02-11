audio_bus_open(void)
{
	int i, s;
	if(_is_open)
		return;

	memset(bustab, 0, sizeof(bustab));
	for(i = 0; i < AUDIO_MAX_BUSSES; ++i)
	{
		for(s = 0; s < AUDIO_MAX_INSERTS; ++s)
			memcpy(bustab[i].bctl[s], a_bus_def_ctl,
					sizeof(a_bus_def_ctl));
		dcf6s_init(&bustab[i].dcfilter, a_settings.samplerate);
		dcf6s_set_f(&bustab[i].dcfilter, 10);
		bustab[i].in_use = 0;
	}
	_is_open = 1;
}
