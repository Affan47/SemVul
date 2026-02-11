ne_close_connection(ne_session *sess)
{
    if (sess->connected) {
	NE_DEBUG(NE_DBG_SOCKET, "Closing connection.\n");
	ne_sock_close(sess->socket);
	sess->socket = NULL;
	NE_DEBUG(NE_DBG_SOCKET, "Connection closed.\n");
    } else {
	NE_DEBUG(NE_DBG_SOCKET, "(Not closing closed connection!).\n");
    }
    sess->connected = 0;
}
