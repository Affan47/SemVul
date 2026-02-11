think_new_independent_town()
{
	if( misc.random(3) != 0 )
		return;


	Town* townPtr;
	int   independentTownCount=0, allTotalPop=0;

	int i;
	for( i=town_array.size() ; i>0 ; i-- )
	{
		if( town_array.is_deleted(i) )
			continue;

		townPtr = town_array[i];

		allTotalPop += townPtr->population;

		if( townPtr->nation_recno == 0 )
			independentTownCount++;
	}

	if( independentTownCount >= 10 )
		return;


	if( allTotalPop > 1000 )
		return;


	for( i=0 ; i<MAX_RACE ; i++ )
	{
		race_wander_pop_array[i] += 2+misc.random(5);
	}


	int raceId = misc.random(MAX_RACE)+1;

	for( i=0 ; i<MAX_RACE ; i++ )
	{
		if( ++raceId > MAX_RACE )
			raceId = 1;

		if( race_wander_pop_array[raceId-1] >= 10 )
			break;
	}

	if( i==MAX_RACE )
		return;


	int xLoc, yLoc;

	if( !think_town_loc(MAX_WORLD_X_LOC*MAX_WORLD_Y_LOC/4, xLoc, yLoc) )
		return;


	int townRecno  = town_array.add_town(0, raceId, xLoc, yLoc);
	int maxTownPop = 20 + misc.random(10);
	int addPop, townResistance;
	int loopCount=0;

	townPtr = town_array[townRecno];

	while(1)
	{
		err_when( loopCount++ > 100 );

		addPop = race_wander_pop_array[raceId-1];
		addPop = MIN(maxTownPop-townPtr->population, addPop);

		townResistance = independent_town_resistance();

		townPtr->init_pop( raceId, addPop, townResistance, 0, 1 );

		race_wander_pop_array[raceId-1] -= addPop;

		err_when( race_wander_pop_array[raceId-1] < 0 );

		if( townPtr->population >= maxTownPop )
			break;


		raceId = misc.random(MAX_RACE)+1;

		for( i=0 ; i<MAX_RACE ; i++ )
		{
			if( ++raceId > MAX_RACE )
				raceId = 1;

			if( race_wander_pop_array[raceId-1] >= 5 )
				break;
		}

		if( i==MAX_RACE )
			break;
	}


	townPtr->auto_set_layout();


}
