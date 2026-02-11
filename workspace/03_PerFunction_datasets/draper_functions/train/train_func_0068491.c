player_get_purchase_unit_limit( Player *player )
{
	int limit = player->unit_limit;
	Unit *u = NULL;

	if (limit == 0)
		return -1;


	list_reset( units );
	while ((u = list_next( units )))
		if (u->player == player && u->killed == 0)
			limit--;

	list_reset( reinf );
	while ((u = list_next( reinf )))
		if (u->player == player)
			limit--;

	limit -= avail_units->count;

	return limit;
}
