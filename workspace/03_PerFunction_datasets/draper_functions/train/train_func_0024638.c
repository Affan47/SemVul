player_can_purchase_unit( Player *p, Unit_Lib_Entry *unit,
							Unit_Lib_Entry *trsp)
{
	int cost = unit->cost + ((trsp)?trsp->cost:0);

	if (player_get_purchase_unit_limit(p) == 0)
		return 0;
	if (p->cur_prestige < cost)
		return 0;
	return 1;
}
