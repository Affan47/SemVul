change_all_people_loyalty(int loyaltyChange, int raceId)
{


	Unit* unitPtr;

	int i;
	for( i=unit_array.size() ; i>0 ; i-- )
	{
		if( unit_array.is_deleted(i) )
			continue;

		if( i==king_unit_recno )
			continue;

		unitPtr = unit_array[i];

		if( unitPtr->nation_recno != nation_recno )
			continue;


		if( !raceId || unitPtr->race_id == raceId )
			unitPtr->change_loyalty(loyaltyChange);
	}


	Firm* firmPtr;

	for( i=firm_array.size() ; i>0 ; i-- )
	{
		if( firm_array.is_deleted(i) )
			continue;

		firmPtr = firm_array[i];

		if( firmPtr->nation_recno != nation_recno )
			continue;


		if( firmPtr->firm_id == FIRM_CAMP || firmPtr->firm_id == FIRM_BASE )
		{
			Worker* workerPtr = firmPtr->worker_array;

			for(int j=firmPtr->worker_count-1 ; j>=0 ; j--, workerPtr++ )
			{
				if( !raceId || workerPtr->race_id == raceId )
					workerPtr->change_loyalty(loyaltyChange);
			}
		}
	}


	Town* townPtr;

	for( i=town_array.size() ; i>0 ; i-- )
	{
		if( town_array.is_deleted(i) )
			continue;

		townPtr = town_array[i];

		if( townPtr->nation_recno != nation_recno )
			continue;


		if( raceId )
		{
			if( townPtr->race_pop_array[raceId-1] > 0 )
				townPtr->change_loyalty(raceId, (float) loyaltyChange);
		}
		else
		{
			for(int j=0 ; j<MAX_RACE ; j++ )
			{
				if( townPtr->race_pop_array[j]==0 )
					continue;

				townPtr->change_loyalty(j+1, (float) loyaltyChange);
			}
		}
	}
}
