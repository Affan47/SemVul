set_power(int xLoc1, int yLoc1, int xLoc2, int yLoc2, int nationRecno)
{


	int	plateauResult = (get_loc((xLoc1+xLoc2)/2, (yLoc1+yLoc2)/2)->is_plateau()==1);

	int   	 xLoc, yLoc, centerY, t;
	Location* locPtr = loc_matrix;

	xLoc1 = MAX( 0, xLoc1 - EFFECTIVE_POWER_DISTANCE+1);
	yLoc1 = MAX( 0, yLoc1 - EFFECTIVE_POWER_DISTANCE+1);
	xLoc2 = MIN( MAX_WORLD_X_LOC-1, xLoc2 + EFFECTIVE_POWER_DISTANCE-1);
	yLoc2 = MIN( MAX_WORLD_Y_LOC-1, yLoc2 + EFFECTIVE_POWER_DISTANCE-1);

	centerY = (yLoc1+yLoc2) / 2;

	for( yLoc=yLoc1 ; yLoc<=yLoc2 ; yLoc++ )
	{
		t=abs(yLoc-centerY)/2;

		for( xLoc=xLoc1+t ; xLoc<=xLoc2-t ; xLoc++, locPtr++ )
		{
			locPtr = get_loc(xLoc, yLoc);

			if(locPtr->sailable())
				continue;

			if(locPtr->is_power_off())
				continue;

			if((locPtr->is_plateau()==1) != plateauResult)
				continue;

			if(locPtr->power_nation_recno==0)
			{
				locPtr->power_nation_recno = nationRecno;
				sys.map_need_redraw = 1;
			}
		}
	}
}
