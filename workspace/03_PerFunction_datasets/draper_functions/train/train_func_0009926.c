namco_sh_start(const struct MachineSound *msound)
{
	const char *mono_name = "NAMCO sound";
	const char *stereo_names[] =
	{
		"NAMCO sound left",
		"NAMCO sound right"
	};
	sound_channel *voice;
	const struct namco_interface *intf = msound->sound_interface;
	int clock_multiple;


	num_voices = intf->voices;
	last_channel = channel_list + num_voices;


	namco_clock = intf->samplerate;
	for (clock_multiple = 0; namco_clock < INTERNAL_RATE; clock_multiple++)
		namco_clock *= 2;

	f_fracbits = clock_multiple + 15;


	sample_rate = namco_clock / OVERSAMPLING_RATE;

	logerror("Namco: freq fractional bits = %d: internal freq = %d, output freq = %d\n", f_fracbits, namco_clock, sample_rate);


	if (build_decoded_waveform(intf->region))
		return 1;


	if (intf->stereo)
	{
		int vol[2];

		vol[0] = MIXER(intf->volume,MIXER_PAN_LEFT);
		vol[1] = MIXER(intf->volume,MIXER_PAN_RIGHT);
		stream = stream_init_multi(2, stereo_names, vol, sample_rate, 0, namco_update_stereo);
	}
	else
	{
		stream = stream_init(mono_name, intf->volume, sample_rate, 0, namco_update_mono);
	}


	sound_enable = 1;


	for (voice = channel_list; voice < last_channel; voice++)
	{
		voice->frequency = 0;
		voice->volume[0] = voice->volume[1] = 0;
		voice->waveform_select = 0;
		voice->counter = 0;
		voice->noise_sw = 0;
		voice->noise_state = 0;
		voice->noise_seed = 1;
		voice->noise_counter = 0;
	}

	return 0;
}
