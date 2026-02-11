resume_original_attack_action()
{
	if( !original_action_mode )
		return;

	if( original_action_mode != ACTION_ATTACK_UNIT &&
		 original_action_mode != ACTION_ATTACK_FIRM &&
		 original_action_mode != ACTION_ATTACK_TOWN )
	{
		original_action_mode = 0;
		return;
	}


	err_when( original_action_x_loc<0 || original_action_x_loc>=MAX_WORLD_X_LOC );
	err_when( original_action_y_loc<0 || original_action_y_loc>=MAX_WORLD_Y_LOC );

	Location* locPtr = world.get_loc(original_action_x_loc, original_action_y_loc);
	int		 targetNationRecno = -1;

	if( original_action_mode == ACTION_ATTACK_UNIT && locPtr->has_unit(UNIT_LAND) )
	{
		int unitRecno = locPtr->unit_recno(UNIT_LAND);

		if( unitRecno == original_action_para )
			targetNationRecno = unit_array[unitRecno]->nation_recno;
	}
	else if( original_action_mode == ACTION_ATTACK_FIRM && locPtr->is_firm() )
	{
		int firmRecno = locPtr->firm_recno();

		if( firmRecno == original_action_para )
			targetNationRecno = firm_array[firmRecno]->nation_recno;
	}
	else if( original_action_mode == ACTION_ATTACK_TOWN && locPtr->is_town() )
	{
		int townRecno = locPtr->town_recno();

		if( townRecno == original_action_para )
			targetNationRecno = town_array[townRecno]->nation_recno;
	}


	if( targetNationRecno == -1 )
	{
		original_action_mode = 0;
		return;
	}


	if( !targetNationRecno || (targetNationRecno &&
		 targetNationRecno != nation_recno &&
		 nation_array[nation_recno]->get_relation_status(targetNationRecno) == NATION_HOSTILE ))
	{
		short selectedArray[1];
		selectedArray[0] = sprite_recno;


		unit_array.attack(original_action_x_loc, original_action_y_loc, 0, selectedArray, 1, COMMAND_AI, 0 );

	}

	original_action_mode = 0;
}
