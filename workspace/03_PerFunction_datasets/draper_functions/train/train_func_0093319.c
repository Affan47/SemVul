avdtp_abort(struct avdtp *session, struct avdtp_stream *stream)
{
	struct seid_req req;
	int ret;

	if (!g_slist_find(session->streams, stream))
		return -EINVAL;

	if (stream->lsep->state == AVDTP_STATE_ABORTING)
		return -EINVAL;

	if (session->req && stream == session->req->stream)
		return cancel_request(session, ECANCELED);

	memset(&req, 0, sizeof(req));
	req.acp_seid = stream->rseid;

	ret = send_request(session, TRUE, stream, AVDTP_ABORT,
							&req, sizeof(req));
	if (ret == 0)
		stream->abort_int = TRUE;

	return ret;
}
