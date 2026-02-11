suspend_ind(struct avdtp *session, struct avdtp_local_sep *sep,
				struct avdtp_stream *stream, uint8_t *err,
				void *user_data)
{
	struct a2dp_sep *a2dp_sep = user_data;
	struct a2dp_setup *setup;
	gboolean start;
	int start_err;

	if (a2dp_sep->type == AVDTP_SEP_TYPE_SINK)
		DBG("Sink %p: Suspend_Ind", sep);
	else
		DBG("Source %p: Suspend_Ind", sep);

	if (a2dp_sep->suspend_timer) {
		g_source_remove(a2dp_sep->suspend_timer);
		a2dp_sep->suspend_timer = 0;
		avdtp_unref(a2dp_sep->session);
		a2dp_sep->session = NULL;
	}

	if (!a2dp_sep->suspending)
		return TRUE;

	a2dp_sep->suspending = FALSE;

	setup = find_setup_by_session(session);
	if (!setup)
		return TRUE;

	start = setup->start;
	setup->start = FALSE;

	finalize_suspend(setup);

	if (!start)
		return TRUE;

	start_err = avdtp_start(session, a2dp_sep->stream);
	if (start_err < 0 && start_err != -EINPROGRESS) {
		error("avdtp_start: %s (%d)", strerror(-start_err),
								-start_err);
		finalize_setup_errno(setup, start_err, finalize_resume);
	}

	return TRUE;
}
