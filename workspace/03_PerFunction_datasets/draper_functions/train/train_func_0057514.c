init(void)
{
	esd_format_t esd_fmt;
	int i;
	int fl;
	char *server = NULL;

	esd_lib_handle = dlopen("libesd.so", RTLD_NOW | RTLD_GLOBAL | RTLD_NODELETE);
	if(esd_lib_handle == NULL) {
		return 0;
	}

	for(i=0; esd_array[i].name; i++) {
		dlerror();
		*(void**) esd_array[i].funcpp = dlsym(esd_lib_handle,esd_array[i].name);
		if(dlerror() != NULL) {
			return 0;
		}
	}

	if (esd_fd < 0) {
		esd_fd = e_open_sound(server);
		if (esd_fd < 0) {
			return 0;
		}
		esd_svinfo = e_get_server_info(esd_fd);
	}

	esd_fmt = ESD_STREAM | ESD_PLAY;
	esd_samplerate = GLUE_AUDIO_RATE;

#if 0

	if (esd_svinfo != NULL)
		esd_sampelrate = esd_svinfo->rate;
#endif

#if GLUE_AUDIO_CHANNELS == 1
	esd_fmt |= ESD_MONO;
	esd_bytes_per_sample = 1;
#elif GLUE_AUDIO_CHANNELS == 2
	esd_fmt |= ESD_STEREO;
	esd_bytes_per_sample = 2;
#else
#error unsupported number of channels
#endif

#if GLUE_AUDIO_FORMAT == AFMT_U8 || GLUE_AUDIO_FORMAT == AFMT_S8
	esd_fmt |= ESD_BITS8;
#else
	esd_fmt |= ESD_BITS16;
	esd_bytes_per_sample *= 2;
#endif
	esd_play_fd = e_play_stream_fallback(esd_fmt, esd_samplerate,
			server, ESD_CLIENT_NAME);
	if (esd_play_fd < 0) {
		return 0;
	}


	if ((fl = fcntl(esd_play_fd, F_GETFL)) >= 0)
		fcntl(esd_play_fd, F_SETFL, O_NDELAY|fl);

	esd_bps = esd_bytes_per_sample * esd_samplerate;

	esd_play_start.tv_sec = 0;
	esd_samples_written = 0;

	return 1;
}
