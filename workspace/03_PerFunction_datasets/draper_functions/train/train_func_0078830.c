ai_goal_purge_invalid_goals( ai_goal *aigp, ai_goal *goal_list, ai_info *aip, int ai_wingnum )
{
	int i, j;
	ai_goal *purge_goal;
	char *name;
	int mode, ship_index, wingnum;


	name = aigp->target_name;
	mode = aigp->ai_mode;


	ship_index = ship_name_lookup(name);
	if ( ship_index == -1 ) {
		Int3();
		return;
	}
	wingnum = Ships[ship_index].wingnum;

	purge_goal = goal_list;
	for ( i = 0; i < MAX_AI_GOALS; purge_goal++, i++ ) {
		int purge_ai_mode, purge_wing;

		purge_ai_mode = purge_goal->ai_mode;


		if ( purge_ai_mode == AI_GOAL_NONE )
			continue;


		if ( purge_goal->target_name == NULL )
			continue;


		purge_wing = wing_name_lookup( purge_goal->target_name, 1 );


		if ( purge_wing == -1 ) {
			if ( stricmp(purge_goal->target_name, name ) )
				continue;
		} else if ( purge_wing != wingnum )
			continue;

		switch (mode)
		{

			case AI_GOAL_IGNORE:
			case AI_GOAL_IGNORE_NEW:
				if ( purge_ai_mode & (AI_GOAL_DISABLE_SHIP | AI_GOAL_DISARM_SHIP | AI_GOAL_CHASE | AI_GOAL_CHASE_WING | AI_GOAL_DESTROY_SUBSYSTEM) )
					purge_goal->flags |= AIGF_PURGE;
				break;


			case AI_GOAL_DISARM_SHIP:
			case AI_GOAL_DISABLE_SHIP:
				if ( purge_ai_mode & (AI_GOAL_CHASE | AI_GOAL_CHASE_WING) ) {
					int ai_ship_type;


					if (ai_wingnum >= 0) {
						ai_ship_type = Ship_info[Ships[Wings[ai_wingnum].special_ship].ship_info_index].class_type;
					}

					else {
						Assert(aip != NULL);
						ai_ship_type = Ship_info[Ships[aip->shipnum].ship_info_index].class_type;
					}


					ship_type_info *crippled_ships_type = &Ship_types[Ship_info[Ships[ship_index].ship_info_index].class_type];


					for ( j=0 ; j < (int)crippled_ships_type->ai_cripple_ignores.size(); j++) {
						if (crippled_ships_type->ai_cripple_ignores[j] == ai_ship_type) {
								purge_goal->flags |= AIGF_PURGE;
						}
					}
				}
				break;
		}
	}
}
