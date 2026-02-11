avdtp_abort_resp(struct avdtp *session,
					struct avdtp_stream *stream,
					struct seid_rej *resp, int size)
{
	struct avdtp_local_sep *sep = stream->lsep;

	avdtp_sep_set_state(session, sep, AVDTP_STATE_ABORTING);

	if (sep->cfm && sep->cfm->abort)
		sep->cfm->abort(session, sep, stream, NULL, sep->user_data);

	avdtp_sep_set_state(session, sep, AVDTP_STATE_IDLE);

	return TRUE;
}
