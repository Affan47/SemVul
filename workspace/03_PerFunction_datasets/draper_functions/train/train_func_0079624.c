process_wait()
{
	err_when((check_unit_dir1=get_dir(cur_x, cur_y, go_x, go_y))!=final_dir);
	if(!match_dir())
		return;


	err_when( (go_x>>ZOOM_X_SHIFT_COUNT!=move_to_x_loc || go_y>>ZOOM_Y_SHIFT_COUNT!=move_to_y_loc) &&
				 ( (cur_x==go_x && cur_y==go_y) || (cur_x!=next_x || cur_y!=next_y) ) );

	if(next_x_loc()==move_to_x_loc && next_y_loc()==move_to_y_loc && !swapping)
	{
		terminate_move();
		return;
	}

   int stepMagn = move_step_magn();
	int nextX = cur_x+stepMagn*move_x_pixel_array[final_dir];
   int nextY = cur_y+stepMagn*move_y_pixel_array[final_dir];


	short x = nextX>>ZOOM_X_SHIFT_COUNT;
	short y = nextY>>ZOOM_Y_SHIFT_COUNT;
	Location *locPtr = world.get_loc(x, y);
	short blocked = ( (!locPtr->is_accessible(mobile_type)) || (locPtr->has_unit(mobile_type) &&
							locPtr->unit_recno(mobile_type)!=sprite_recno) );

	if(!blocked || move_action_call_flag)
	{

		waiting_term = 0;
		set_move();
		cur_frame  = 1;
		set_next(nextX, nextY, -stepMagn, 1);
	}
	else
	{


		err_when(cur_x!=next_x || cur_y!=next_y);
      handle_blocked_move(locPtr);
	}

	err_when(cur_action==SPRITE_MOVE && (cur_x!=go_x || cur_y!=go_y) && (cur_x==next_x && cur_y==next_y));
	err_when(cur_x==go_x && cur_y==go_y && (cur_x!=next_x || cur_y!=next_y));
}
