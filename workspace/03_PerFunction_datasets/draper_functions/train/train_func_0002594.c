detect_info()
{
	if( detect_basic_info() )
		return;

	if( detect_unit_profile() )
		return;

	if( !is_own() )
		return;

	if( game.game_mode == GAME_TEST )
		return;

	if( god_res[god_id]->can_cast_power )
	{

		int rc=0;
		char castPowerType = 0;

		if( button_cast.detect() )
		{

			castPowerType = 1;
			rc = 1;
		}

		if( button_cast2.detect() )
		{
			castPowerType = 2;


			rc = 1;
		}


		if( rc && castPowerType)
		{
			if( god_id == GOD_VIKING && castPowerType == 1 )
				go_cast_power(next_x_loc(), next_y_loc(), castPowerType, COMMAND_PLAYER);
			else
				power.issue_command(COMMAND_GOD_CAST_POWER, sprite_recno, castPowerType);
		}

	}
}
