is_on_coast()
{
	Location *locPtr;
	int 		xShift, yShift, checkXLoc, checkYLoc, found=0;
	int 		curXLoc = next_x_loc();
	int 		curYLoc = next_y_loc();

	for(int i=2; i<=9; i++)
	{
		misc.cal_move_around_a_point(i, 3, 3, xShift, yShift);

		checkXLoc = curXLoc + xShift;
		checkYLoc = curYLoc + yShift;

		if(checkXLoc<0 || checkXLoc>=MAX_WORLD_X_LOC || checkYLoc<0 || checkYLoc>=MAX_WORLD_Y_LOC)
			continue;

		locPtr = world.get_loc(checkXLoc, checkYLoc);

		if(terrain_res[locPtr->terrain_id]->average_type!=TERRAIN_OCEAN &&
			locPtr->walkable())
		{
			return 1;
		}
	}

	return 0;
}
