think_persian_god()
{


	Nation* ownNation = nation_array[nation_recno];
	Firm*	  firmPtr;
	int  	  curRating, bestRating=0;
	int	  targetXLoc, targetYLoc;

	for( int i=ownNation->ai_camp_count-1 ; i>=0 ; i-- )
	{
		firmPtr = firm_array[ ownNation->ai_camp_array[i] ];


		Worker* workerPtr = firmPtr->worker_array;
		int	  totalHitPoints = 0;
		int	  totalMaxHitPoints = 0;

		for( int j=0 ; j<firmPtr->worker_count ; j++, workerPtr++ )
		{
			totalHitPoints 	+= workerPtr->hit_points;
			totalMaxHitPoints += workerPtr->max_hit_points();
		}

		if( !totalMaxHitPoints )
			continue;

		curRating = 100 * (totalMaxHitPoints-totalHitPoints) / totalMaxHitPoints;


		if( firmPtr->overseer_recno &&
			 unit_array[firmPtr->overseer_recno]->rank_id == RANK_KING )
		{
			curRating += 20;
		}

		if( curRating > bestRating )
		{
			bestRating = curRating;
			targetXLoc = firmPtr->center_x;
			targetYLoc = firmPtr->center_y;
		}
	}


	if( bestRating )
	{
		go_cast_power(targetXLoc, targetYLoc, 1, COMMAND_AI);
	}
}
