spy_bribe_succeed_chance(int bribeAmount, short briberSpyRecno, short workerId)
{
	Spy* spyPtr = spy_array[briberSpyRecno];

	err_when( spyPtr->spy_place != SPY_FIRM );
	err_when( spyPtr->spy_place_para != firm_recno );


	int unitLoyalty, unitRaceId, targetSpyRecno, unitCommandPower;

	if( workerId )
	{
		Worker* workerPtr = worker_array+workerId-1;

		unitLoyalty = workerPtr->loyalty();
		unitRaceId  = workerPtr->race_id;
		unitCommandPower = 0;
		targetSpyRecno = workerPtr->spy_recno;
	}
	else if( overseer_recno )
	{
		Unit* unitPtr = unit_array[overseer_recno];

		unitLoyalty = unitPtr->loyalty;
		unitRaceId  = unitPtr->race_id;
		unitCommandPower = unitPtr->commander_power();
		targetSpyRecno = unitPtr->spy_recno;
	}
	else
		err_here();

	err_when( unitRaceId < 1 || unitRaceId > MAX_RACE );


	int succeedChance;

	if( targetSpyRecno )
	{
		err_when( spy_array[targetSpyRecno]->true_nation_recno == spyPtr->true_nation_recno );

		succeedChance = 0;
	}
	else
	{
		succeedChance = spyPtr->spy_skill - unitLoyalty - unitCommandPower
							 + (int) nation_array[spyPtr->true_nation_recno]->reputation
							 + 200 * bribeAmount / MAX_BRIBE_AMOUNT;


		int spyKingRaceId = nation_array[ spyPtr->true_nation_recno ]->race_id;

		succeedChance += race_res.is_same_race(spyPtr->race_id, unitRaceId) * 10 +
							  race_res.is_same_race(spyKingRaceId, unitRaceId) * 10;

		if( unitLoyalty > 60 )
			succeedChance -= (unitLoyalty-60);

		if( unitLoyalty > 70 )
			succeedChance -= (unitLoyalty-70);

		if( unitLoyalty > 80 )
			succeedChance -= (unitLoyalty-80);

		if( unitLoyalty > 90 )
			succeedChance -= (unitLoyalty-90);

		if( unitLoyalty == 100 )
			succeedChance = 0;
	}

	return succeedChance;
}
