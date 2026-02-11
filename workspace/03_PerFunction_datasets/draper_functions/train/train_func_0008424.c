print_sdp(sdp_info_t* sdp, int log_level)
{
	sdp_session_cell_t *session;

	LM_GEN1(log_level, "sdp:%p=>%p (%d:%d)\n", sdp, sdp->sessions, sdp->sessions_num, sdp->streams_num);
	session = sdp->sessions;
	while (session) {
		print_sdp_session(session, log_level);
		session = session->next;
	}
}
