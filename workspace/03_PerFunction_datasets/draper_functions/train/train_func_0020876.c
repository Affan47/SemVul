init() {
	struct pa_sample_spec ss;
	struct pa_buffer_attr a;
	int i;

	pulse_lib_handle = dlopen("libpulse.so.0", RTLD_NOW | RTLD_GLOBAL | RTLD_NODELETE);
	if (pulse_lib_handle == NULL) {
		return 0;
	}

	for (i=0; pulse_array[i].name; i++) {
		dlerror();
		*(void**) pulse_array[i].funcpp = dlsym(pulse_lib_handle,pulse_array[i].name);
		if (dlerror() != NULL) {
			return 0;
		}
	}

	ss.channels = GLUE_AUDIO_CHANNELS;
	ss.rate = GLUE_AUDIO_RATE;

#if GLUE_AUDIO_FORMAT == AFMT_S16_LE
	ss.format = PA_SAMPLE_S16LE;
#elif GLUE_AUDIO_FORMAT == AFMT_S16_BE
	ss.format = PA_SAMPLE_S16BE;
#else
#error unsupported format
#endif

	if (!p_sample_spec_valid(&ss)) {
		goto fail;
	}

	mainloop = p_mainloop_new();

	context = p_context_new(p_mainloop_get_api(mainloop), PULSE_CLIENT_NAME);

	p_context_connect(context, NULL, PA_CONTEXT_NOAUTOSPAWN, NULL);

	wait_for_completion();

	if (p_context_get_state(context) != PA_CONTEXT_READY) {
		goto fail;
	}

	stream = p_stream_new(context, "audio stream", &ss, NULL);

	a.maxlength = p_bytes_per_second(&ss)*1;
	a.tlength = a.maxlength*9/10;
	a.prebuf = a.tlength/2;
	a.minreq = a.tlength/10;

	p_stream_connect_playback(stream, NULL, &a, PA_STREAM_INTERPOLATE_TIMING, NULL, NULL);

	wait_for_completion();

	if (p_stream_get_state(stream) != PA_STREAM_READY) {
		goto fail;
	}

	return 1;

fail:
	uninit(1);
	return 0;
}
