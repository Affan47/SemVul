detect_surround_target()
{
	#define DIMENSION		3
	#define CHECK_SIZE	DIMENSION*DIMENSION

	int curXLoc = next_x_loc();
	int curYLoc = next_y_loc();
	int checkXLoc, checkYLoc, xShift, yShift;
	Unit *targetPtr;
	Location *locPtr;
	short targetRecno;

	for(int i=2; i<=CHECK_SIZE; ++i)
	{
		misc.cal_move_around_a_point(i, DIMENSION, DIMENSION, xShift, yShift);
      checkXLoc = curXLoc+xShift;
      checkYLoc = curYLoc+yShift;
      if(checkXLoc<0 || checkXLoc>=MAX_WORLD_X_LOC || checkYLoc<0 || checkYLoc>=MAX_WORLD_Y_LOC)
         continue;

      locPtr = world.get_loc(checkXLoc, checkYLoc);

		if(locPtr->has_unit(UNIT_LAND))
		{
			targetRecno = locPtr->unit_recno(UNIT_LAND);
			if(unit_array.is_deleted(targetRecno))
				continue;

			targetPtr = unit_array[targetRecno];
			if(targetPtr->nation_recno==nation_recno)
				continue;

			if(idle_detect_unit_checking(targetRecno))
			{
				attack_unit(targetRecno);
				return 1;
			}
		}
	}

	return 0;
}
