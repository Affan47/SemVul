sink_shutdown(struct sink *sink)
{
	if (!sink->session)
		return FALSE;

	avdtp_set_device_disconnect(sink->session, TRUE);


	if (sink->connect) {
		struct pending_request *pending = sink->connect;

		if (pending->msg)
			error_failed(pending->conn, pending->msg,
							"Stream setup failed");
		pending_request_free(sink->dev, pending);
		sink->connect = NULL;

		avdtp_unref(sink->session);
		sink->session = NULL;

		return TRUE;
	}


	if (sink->disconnect)
		return TRUE;

	if (!sink->stream)
		return FALSE;

	if (avdtp_close(sink->session, sink->stream, FALSE) < 0)
		return FALSE;

	return TRUE;
}
