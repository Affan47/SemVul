gfire_sq_gamespy3_query(gfire_game_server *p_server, gboolean p_full, int p_socket)
{
	static const guint8 challengeQuery[]	= { 0xfe, 0xfd, 0x09, 'G', 'F', 'S', 'Q' };
	static guint8 dataQuery[]				= { 0xfe, 0xfd, 0x00, 'G', 'F', 'S', 'Q',
												0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00,
												0x01};

	int len;
	const guint8 *query;
	if(!p_server->data)
	{
		len = sizeof(challengeQuery);
		query = challengeQuery;
	}
	else
	{
		gfire_sq_gamespy3_data *data = (gfire_sq_gamespy3_data*)p_server->data->proto_data;
		memcpy(dataQuery + 7, &data->challenge, 4);

		dataQuery[12] = p_full ? 0xff : 0x00;
		dataQuery[13] = p_full ? 0xff : 0x00;

		len = sizeof(dataQuery);
		query = dataQuery;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = g_htonl(p_server->ip);
	addr.sin_port = g_htons(p_server->query_port);

	sendto(p_socket, query, len, 0, (struct sockaddr*)&addr, sizeof(addr));
}
