build_wall(int townRecno, short initHp)
{
	Town* townPtr = town_array[townRecno];

	int xLoc1 = MAX(0, townPtr->loc_x1-WALL_SPACE_LOC);
	int yLoc1 = MAX(0, townPtr->loc_y1-WALL_SPACE_LOC);
	int xLoc2 = MIN(MAX_WORLD_X_LOC-1, townPtr->loc_x2+WALL_SPACE_LOC);
	int yLoc2 = MIN(MAX_WORLD_Y_LOC-1, townPtr->loc_y2+WALL_SPACE_LOC);


	build_wall_section(xLoc1, yLoc1, xLoc2, yLoc2, townRecno, initHp);
}
