gfire_game_by_id(guint32 p_gameid)
{
	GList *cur = gfire_games;
	for(; cur; cur = g_list_next(cur))
	{
		if(((gfire_game*)cur->data)->id == p_gameid)
			return (gfire_game*)cur->data;
	}

	return NULL;
}
