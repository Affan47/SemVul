server_idle_next(IRC_SERVER_REC *server)
{
	SERVER_IDLE_REC *rec;

	g_return_if_fail(server != NULL);

	if (server->idles == NULL)
		return;
	rec = server->idles->data;


	if (rec->redirect_cmd != NULL) {
		server_redirect_event_list(server, rec->redirect_cmd,
					   rec->count, rec->arg,
					   rec->remote, rec->failure_signal,
					   rec->redirects);
	}
	irc_send_cmd(server, rec->cmd);

	server_idle_destroy(server, rec);
}
