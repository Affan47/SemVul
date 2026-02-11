gfire_sq_gamespy2_parse(gfire_game_server *p_server, guint16 p_ping, gboolean p_full,
									 const unsigned char *p_data, guint p_len)
{

	if(p_data[0] != 0 || memcmp(p_data + 1, "GFSQ", 4) != 0)
		return FALSE;

	p_server->data = g_new0(gfire_game_server_data, 1);
	p_server->data->driver = &gf_sq_gamespy2_driver;
	p_server->data->ping = p_ping;

	gfire_sq_gamespy2_data *gsdata = p_server->data->proto_data = g_new0(gfire_sq_gamespy2_data, 1);


	guint offset = 5;
	offset += gfire_sq_gamespy2_parseInfo(gsdata, p_data + offset, p_len - offset);

	if(g_datalist_get_data(&gsdata->info, "hostname"))
		p_server->data->name = g_strdup(g_datalist_get_data(&gsdata->info, "hostname"));
	if(g_datalist_get_data(&gsdata->info, "mapname"))
		p_server->data->map = g_strdup(g_datalist_get_data(&gsdata->info, "mapname"));
	if(g_datalist_get_data(&gsdata->info, "numplayers"))
		sscanf(g_datalist_get_data(&gsdata->info, "numplayers"), "%u", &p_server->data->players);
	if(g_datalist_get_data(&gsdata->info, "maxplayers"))
		sscanf(g_datalist_get_data(&gsdata->info, "maxplayers"), "%u", &p_server->data->max_players);

	if(p_full)
	{

		offset += gfire_sq_gamespy2_parsePlayers(gsdata, p_data + offset, p_len - offset);
	}

	return FALSE;
}
