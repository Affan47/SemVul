sig_window_changed(WINDOW_REC *window, WINDOW_REC *oldwindow)
{
	XMPP_SERVER_REC *server;

	g_return_if_fail(window != NULL);
	if ((server = XMPP_SERVER(window->active_server)) == NULL)
		return;
	update_nick_statusbar(server, MUC(window->active), FALSE);
}
