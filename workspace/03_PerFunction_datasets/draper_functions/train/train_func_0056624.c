gfire_free(gfire_data *p_gfire)
{
	if(!p_gfire)
		return;

	if(p_gfire->sid) g_free(p_gfire->sid);
	if(p_gfire->buff_in) g_free(p_gfire->buff_in);


	while(p_gfire->buddies)
	{
		gfire_buddy_free((gfire_buddy*)p_gfire->buddies->data);
		p_gfire->buddies = g_list_delete_link(p_gfire->buddies, p_gfire->buddies);
	}


	while(p_gfire->clans)
	{
		gfire_clan_free((gfire_clan*)p_gfire->clans->data);
		p_gfire->clans = g_list_delete_link(p_gfire->clans, p_gfire->clans);
	}


	while(p_gfire->groups)
	{
		gfire_group_free((gfire_group*)p_gfire->groups->data, FALSE);
		p_gfire->groups = g_list_delete_link(p_gfire->groups, p_gfire->groups);
	}


	while(p_gfire->chats)
	{
		gfire_chat_free((gfire_chat*)p_gfire->chats->data);
		p_gfire->chats = g_list_delete_link(p_gfire->chats, p_gfire->chats);
	}

	if(p_gfire->p2p)
		gfire_p2p_connection_close(p_gfire->p2p);

#ifdef USE_GAME_DETECTION

	gfire_game_detector_unregister(p_gfire);
#endif


	gfire_preferences_free(p_gfire->prefs);

	g_free(p_gfire);

	gfire_network_cleanup();
}
