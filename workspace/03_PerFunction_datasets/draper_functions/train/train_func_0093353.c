handle_blocked_same_target_attack(Unit* unitPtr, Unit* targetPtr)
{


	err_when(cur_x%ZOOM_LOC_WIDTH || cur_y%ZOOM_LOC_HEIGHT);
	err_when(cur_x!=next_x || cur_y!=next_y);
	err_when(cur_x==go_x && cur_y==go_y);

	if(space_for_attack(action_x_loc, action_y_loc, targetPtr->mobile_type, targetPtr->sprite_info->loc_width, targetPtr->sprite_info->loc_height))
	{
		err_when(action_x_loc!=action_x_loc2 || action_y_loc!=action_y_loc2);
		search_or_stop(move_to_x_loc, move_to_y_loc, 1, SEARCH_MODE_TO_ATTACK, targetPtr->sprite_recno);

	}
	else if(in_any_defense_mode())
	{
		err_when(action_mode2!=ACTION_AUTO_DEFENSE_ATTACK_TARGET && action_mode2!=ACTION_DEFEND_TOWN_ATTACK_TARGET &&
					action_mode2!=ACTION_MONSTER_DEFEND_ATTACK_TARGET);

		general_defend_mode_detect_target();
	}
	else if(misc.points_distance(next_x_loc(), next_y_loc(), action_x_loc, action_y_loc)<ATTACK_DETECT_DISTANCE)
	{


		stop2(KEEP_DEFENSE_MODE);
	}
	else
		set_wait();
}
