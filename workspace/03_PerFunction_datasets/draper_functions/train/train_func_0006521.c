think_repair()
{
	Nation* ownNation = nation_array[nation_recno];


	if( hit_points >=
		 max_hit_points * (70+ownNation->pref_repair_concern/4) / 100 )
	{
		return;
	}


	if( hit_points >= max_hit_points * 80 / 100 )
	{
		if( ownNation->total_jobless_population < 15 )
			return;
	}


	ownNation->add_action(loc_x1, loc_y1, -1, -1, ACTION_AI_ASSIGN_CONSTRUCTION_WORKER, firm_id);
}
