gfire_buddy_set_game_client_data(gfire_buddy *p_buddy, GList *p_data)
{
	if(!p_buddy || !p_data)
		return;

	while(p_buddy->game_client_data)
	{
		gfire_game_client_data_free(p_buddy->game_client_data->data);
		p_buddy->game_client_data = g_list_delete_link(p_buddy->game_client_data, p_buddy->game_client_data);
	}

	p_buddy->game_client_data = p_data;
}
