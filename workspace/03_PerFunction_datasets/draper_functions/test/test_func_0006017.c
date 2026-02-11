print_sdp_session(sdp_session_cell_t *session, int log_level)
{
	sdp_stream_cell_t *stream = session->streams;

	if (session==NULL) {
		LM_ERR("NULL session\n");
		return;
	}

	LM_GEN1(log_level, "..session[%d]:%p=>%p '%.*s' '%.*s' '%.*s' '%.*s:%.*s' (%d)=>%p\n",
		session->session_num, session, session->next,
		session->cnt_disp.len, session->cnt_disp.s,
		session->ip_addr.len, session->ip_addr.s,
		session->o_ip_addr.len, session->o_ip_addr.s,
		session->bw_type.len, session->bw_type.s, session->bw_width.len, session->bw_width.s,
		session->streams_num, session->streams);
	while (stream) {
		print_sdp_stream(stream, log_level);
		stream=stream->next;
	}
}
