avdtp_start_resp(struct avdtp *session,
					struct avdtp_stream *stream,
					struct seid_rej *resp, int size)
{
	struct avdtp_local_sep *sep = stream->lsep;

	if (sep->cfm && sep->cfm->start)
		sep->cfm->start(session, sep, stream, NULL, sep->user_data);


	if (sep->state != AVDTP_STATE_STREAMING)
		avdtp_sep_set_state(session, sep, AVDTP_STATE_STREAMING);

	return TRUE;
}
