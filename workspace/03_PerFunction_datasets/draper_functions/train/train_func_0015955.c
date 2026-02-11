avdtp_discover(struct avdtp *session, avdtp_discover_cb_t cb,
			void *user_data)
{
	int err;

	if (session->discov_cb)
		return -EBUSY;

	if (session->seps) {
		session->discov_cb = cb;
		session->user_data = user_data;
		g_idle_add(process_discover, session);
		return 0;
	}

	err = send_request(session, FALSE, NULL, AVDTP_DISCOVER, NULL, 0);
	if (err == 0) {
		session->discov_cb = cb;
		session->user_data = user_data;
	}

	return err;
}
