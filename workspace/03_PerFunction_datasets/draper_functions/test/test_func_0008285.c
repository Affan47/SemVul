audio_start(int rate, int latency, int use_oss, int use_midi, int pollaudio)
{
	int i, fragments;
	if(audio_open() < 0)
		return -100;

	audio_stop();

	aev_client("audio_start()");

	a_settings.samplerate = rate;
	using_oss = use_oss;
	using_polling = pollaudio;

	if(sfifo_init(&commands, sizeof(command_t) * MAX_COMMANDS) < 0)
	{
		log_printf(ELOG, "audio.c: Failed to set up audio engine!\n");
		return -1;
	}

	if(ptab_init(65536) < 0)
	{
		log_printf(ELOG, "audio.c: Failed to set up pitch table!\n");
		sfifo_close(&commands);
		return -2;
	}


	audio_channel_open();
	audio_voice_open();
	audio_bus_open();
	if(aev_open(AUDIO_MAX_VOICES * MAX_BUFFER_SIZE) < 0)
	{
		audio_stop();
		return -1;
	}

	if(using_oss)
		fragments = OSS_FRAGMENTS;
	else
		fragments = SDL_FRAGMENTS;
	if(latency > 1000)
		latency = 1000;

	a_settings.output_buffersize = MIN_BUFFER_SIZE;

	while(fragments * a_settings.output_buffersize * 707 /
			 a_settings.samplerate < latency)
		a_settings.output_buffersize <<= 1;
	a_settings.output_buffersize >>= 1;

	log_printf(DLOG, "audio.c: Requested latency %d ms ==>"
			" buffer size: %d samples;"
			" latency: %.2f ms (error: %.2f).\n",
			latency,
			a_settings.output_buffersize,
			fragments * a_settings.output_buffersize * 1000.0 /
					a_settings.samplerate,
			fabs(latency - fragments *
					a_settings.output_buffersize * 1000.0 /
					a_settings.samplerate)
			);

	_audio_pause = 1;

	if(using_polling && !using_oss)
	{
		log_printf(ELOG, "WARNING: Overriding driver selection!"
				" 'pollaudio' requires OSS.\n");
		using_oss = 1;
	}

	if(using_oss)
		i = _start_oss_output();
	else
		i = _start_SDL_output();
	if(i < 0)
	{
		audio_stop();
		return -6;
	}

	if(_open_mixing() < 0)
	{
		audio_stop();
		return -5;
	}

#ifdef DEBUG
	oscbufl = calloc(1, OSCFRAMES*sizeof(int));
	oscbufr = calloc(1, OSCFRAMES*sizeof(int));
	oscframes = OSCFRAMES;
#endif
	midicon_open((float)a_settings.samplerate, 16);

	if(use_midi)
		using_midi = midi_open(&midicon_midisock) >= 0;
	else
		using_midi = 0;

	sequencer_open(&midicon_midisock, (float)a_settings.samplerate);
	audio_wave_prepare(-1);
	aev_reset_timer();

	aev_client("Unknown");
	_audio_pause = 0;
	_wasinit = 1;
	return 0;
}
