n_player_status(xmmsv_t *val, void *connection)
{
	xmmsc_connection_t *conn = (xmmsc_connection_t *)connection;
	gint               status = -1;

	xmmsv_get_int(val, &status);
	if (status == XMMS_PLAYBACK_STATUS_PLAY)
		xmms2ctrl_pause(conn);
	else if (status == XMMS_PLAYBACK_STATUS_PAUSE)
		xmms2ctrl_play(conn);
	return FALSE;
}
