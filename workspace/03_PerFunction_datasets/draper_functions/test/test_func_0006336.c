best_commander_race()
{


	for( int i=linked_town_count-1 ; i>=0 ; i-- )
	{
		Town* townPtr = town_array[ linked_town_array[i] ];

		if( townPtr->closest_own_camp() == firm_recno )
			return townPtr->majority_race();
	}


	int targetTownRecno = think_capture_target_town();

	if( targetTownRecno && town_array[targetTownRecno]->nation_recno==0 )
		return town_array[targetTownRecno]->majority_race();


	return majority_race();
}
