avdtp_set_configuration_resp(struct avdtp *session,
						struct avdtp_stream *stream,
						struct avdtp_single_header *resp,
						int size)
{
	struct avdtp_local_sep *sep = stream->lsep;

	if (sep->cfm && sep->cfm->set_configuration)
		sep->cfm->set_configuration(session, sep, stream, NULL,
						sep->user_data);

	avdtp_sep_set_state(session, sep, AVDTP_STATE_CONFIGURED);

	return TRUE;
}
