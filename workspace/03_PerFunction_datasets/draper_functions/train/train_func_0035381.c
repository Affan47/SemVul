stop2(int preserveAction)
{
	stop(preserveAction);
	reset_action_para2(preserveAction);


	force_move_flag = 0;
	ai_no_suitable_action = 0;

	if( preserveAction==0 )
	{
		original_action_mode = 0;
		ai_original_target_x_loc = -1;

		if( ai_action_id )
			nation_array[nation_recno]->action_failure(ai_action_id, sprite_recno);
	}


}
