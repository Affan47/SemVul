gfire_game_data_reset(gfire_game_data *p_game)
{
	if(!p_game)
		return;

	p_game->id = 0;
	p_game->ip.value = 0;
	p_game->port = 0;
}
