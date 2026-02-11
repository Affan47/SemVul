a2dp_resume(struct avdtp *session, struct a2dp_sep *sep,
				a2dp_stream_cb_t cb, void *user_data)
{
	struct a2dp_setup_cb *cb_data;
	struct a2dp_setup *setup;

	setup = a2dp_setup_get(session);
	if (!setup)
		return 0;

	cb_data = setup_cb_new(setup);
	cb_data->resume_cb = cb;
	cb_data->user_data = user_data;

	setup->sep = sep;
	setup->stream = sep->stream;

	switch (avdtp_sep_get_state(sep->lsep)) {
	case AVDTP_STATE_IDLE:
		goto failed;
		break;
	case AVDTP_STATE_OPEN:
		if (avdtp_start(session, sep->stream) < 0) {
			error("avdtp_start failed");
			goto failed;
		}
		sep->starting = TRUE;
		break;
	case AVDTP_STATE_STREAMING:
		if (!sep->suspending && sep->suspend_timer) {
			g_source_remove(sep->suspend_timer);
			sep->suspend_timer = 0;
			avdtp_unref(sep->session);
			sep->session = NULL;
		}
		if (sep->suspending)
			setup->start = TRUE;
		else
			cb_data->source_id = g_idle_add(finalize_resume,
								setup);
		break;
	default:
		error("SEP in bad state for resume");
		goto failed;
	}

	return cb_data->id;

failed:
	setup_cb_free(cb_data);
	return 0;
}
