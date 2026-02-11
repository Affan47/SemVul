socket_disconnect(struct IPC_CHANNEL* ch)
{
	struct SOCKET_CH_PRIVATE* conn_info;

	conn_info = (struct SOCKET_CH_PRIVATE*) ch->ch_private;
	if (debug_level > 1) {
		cl_log(LOG_DEBUG
		,	"%s(sock=%d, ch=0x%lx){"
		,	__FUNCTION__
		,	conn_info->s, (unsigned long)ch);
	}
#if 0
	if (ch->ch_status != IPC_DISCONNECT) {
  		cl_log(LOG_INFO, "forced disconnect for fd %d", conn_info->s);
	}
#endif
	if (ch->ch_status == IPC_CONNECT) {
		socket_resume_io(ch);
	}

	if (conn_info->s >= 0) {
		if (debug_level > 1) {
			cl_log(LOG_DEBUG
			,	"%s: closing socket %d"
			,	__FUNCTION__, conn_info->s);
		}
		close(conn_info->s);
		cl_poll_ignore(conn_info->s);
		conn_info->s = -1;
	}
	ch->ch_status = IPC_DISCONNECT;
	if (debug_level > 1) {
		cl_log(LOG_DEBUG, "}/*%s(sock=%d, ch=0x%lx)*/"
		,	__FUNCTION__, conn_info->s, (unsigned long)ch);
	}
	return IPC_OK;
}
