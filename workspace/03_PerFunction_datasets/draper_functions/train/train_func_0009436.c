sig_disconnected(IRC_SERVER_REC *server)
{
	if (!IS_IRC_SERVER(server))
		return;

	while (server->rejoin_channels != NULL)
		rejoin_destroy(server, server->rejoin_channels->data);
}
