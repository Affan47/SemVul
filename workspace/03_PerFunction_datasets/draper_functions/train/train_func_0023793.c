validate_mission_goals(int objnum, ai_info *aip)
{
	int	i;


	for ( i = 0; i < MAX_AI_GOALS; i++ ) {
		int		state;
		ai_goal	*aigp;

		aigp = &aip->goals[i];


		if (aigp->ai_mode == AI_GOAL_NONE)
			continue;


		if ( aigp->flags & AIGF_PURGE ) {
			ai_remove_ship_goal( aip, i );
			continue;
		}

		state = ai_mission_goal_achievable( objnum, aigp );


		if ( (state == AI_GOAL_NOT_ACHIEVABLE) || (state == AI_GOAL_SATISFIED) ) {
			ai_remove_ship_goal( aip, i );
			continue;
		}


		if ( (state == AI_GOAL_ACHIEVABLE) && (aigp->flags & AIGF_GOAL_ON_HOLD) )
			aigp->flags &= ~AIGF_GOAL_ON_HOLD;


		if ( state == AI_GOAL_NOT_KNOWN )
			aigp->flags |= AIGF_GOAL_ON_HOLD;
	}


	if ( (aip->goals[0].ai_mode != AI_GOAL_NONE) && (aip->goals[0].flags & AIGF_GOAL_ON_HOLD) )
		aip->mode = AIM_NONE;


	if ( (aip->goals[0].ai_mode == AI_GOAL_REARM_REPAIR) && object_is_docked(&Objects[objnum]) ) {
		for ( i = 1; i < MAX_AI_GOALS; i++ ) {
			if ( (aip->goals[i].ai_mode == AI_GOAL_NONE) || (aip->goals[i].ai_mode == AI_GOAL_REARM_REPAIR) )
				continue;
			aip->goals[i].flags |= AIGF_GOAL_ON_HOLD;
		}
	}
}
