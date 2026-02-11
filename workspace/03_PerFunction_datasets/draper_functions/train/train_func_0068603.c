socket_destroy_channel(struct IPC_CHANNEL * ch)
{
	--ch->refcount;
	if (ch->refcount > 0) {
		return;
	}
	if (ch->ch_status == IPC_CONNECT) {
		socket_resume_io(ch);
	}
	if (debug_level > 1) {
		cl_log(LOG_DEBUG, "socket_destroy(ch=0x%lx){"
		,	(unsigned long)ch);
	}
	socket_disconnect(ch);
	socket_destroy_queue(ch->send_queue);
	socket_destroy_queue(ch->recv_queue);

	if (ch->pool) {
		ipc_bufpool_unref(ch->pool);
	}

	if (ch->ch_private != NULL) {
#if HB_IPC_METHOD == HB_IPC_SOCKET
		struct SOCKET_CH_PRIVATE *priv = (struct SOCKET_CH_PRIVATE *)
			ch->ch_private;
		if(priv->peer_addr != NULL) {
			if (*priv->peer_addr->sun_path) {
				unlink(priv->peer_addr->sun_path);
			}
			g_free((void*)(priv->peer_addr));
		}
#endif
    		g_free((void*)(ch->ch_private));
	}
	memset(ch, 0xff, sizeof(*ch));
	g_free((void*)ch);
	if (debug_level > 1) {
		cl_log(LOG_DEBUG, "}/*socket_destroy(ch=0x%lx)*/"
		,	(unsigned long)ch);
	}
}
