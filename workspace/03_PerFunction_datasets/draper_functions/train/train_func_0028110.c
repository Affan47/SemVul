start_rectangle_floor(int findex)
{
	our_mode = RECTANGLE_FLOOR;


	state.r_start.x = (int)mouse_mapcoord.x;
	state.r_start.y = (int)mouse_mapcoord.y;
	state.r_len_x = 0;
	state.r_len_y = 0;


	state.r_tile_used = findex;

	if (state.r_start.x < 0)
		state.r_start.x = 0;
	else if (state.r_start.x >= EditLevel()->xlen - 1)
		state.r_start.x = EditLevel()->xlen - 1;

	if (state.r_start.y < 0)
		state.r_start.y = 0;
	else if (state.r_start.y >= EditLevel()->ylen - 1)
		state.r_start.y = EditLevel()->ylen - 1;


	action_set_floor(EditLevel(), state.r_start.x, state.r_start.y, state.r_tile_used);
	action_push(ACT_MULTIPLE_ACTIONS, 1);

}
