gfire_fof_game_data_free(fof_game_data *p_data)
{
	if(!p_data)
		return;

	if(p_data->sid) g_free(p_data->sid);
	while(p_data->gcd)
	{
		gfire_game_client_data_free(p_data->gcd->data);
		p_data->gcd = g_list_delete_link(p_data->gcd, p_data->gcd);
	}
	g_free(p_data);
}
