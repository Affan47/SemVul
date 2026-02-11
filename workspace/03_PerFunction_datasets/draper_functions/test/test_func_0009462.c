gfire_game_load_games_xml()
{
	xmlnode *node = NULL;

	gchar *filename = g_build_filename(purple_user_dir(), "gfire_games.xml", NULL);
	if(filename)
	{
		purple_debug(PURPLE_DEBUG_INFO, "gfire", "Loading Game Data from: %s\n", filename);
		g_free(filename);
	}

	node = purple_util_read_xml_from_file("gfire_games.xml", "Gfire Games List");
	if(!node)
	{
		purple_debug(PURPLE_DEBUG_ERROR, "gfire", "gfire_game_load_games_xml: Couldn't load game list.\n");
		return FALSE;
	}


	gfire_game_cleanup();


	if(g_utf8_collate(node->name, "games"))
	{
		xmlnode_free(node);
		return FALSE;
	}

	if(!xmlnode_get_attrib(node, "version"))
		gfire_games_version = 0;
	else
		sscanf(xmlnode_get_attrib(node, "version"), "%u", &gfire_games_version);


	xmlnode *game_node = xmlnode_get_child(node, "game");
	while(game_node)
	{
		gboolean external = FALSE;
		gfire_game *game = gfire_game_create_from_xml(game_node, &external);
		if(game)
		{
			gfire_games = g_list_append(gfire_games, game);
			if(external)
				gfire_games_external = g_list_append(gfire_games_external, game);
		}

		game_node = xmlnode_get_next_twin(game_node);
	}

	xmlnode_free(node);

	return TRUE;
}
