find_best_capturer(int townRecno, int raceId, int& bestTargetResistance)
{
	#define MIN_CAPTURE_RESISTANCE_DEC 	20

	Unit* unitPtr;
	Town* targetTown = town_array[townRecno];
	Firm* firmPtr;
	int   targetResistance;
	int   bestUnitRecno=0;

	bestTargetResistance = 100;

	for( int i=ai_general_count-1 ; i>=0 ; i-- )
	{
		unitPtr = unit_array[ ai_general_array[i] ];

		if( raceId && unitPtr->race_id != raceId )
			continue;

		err_when( unitPtr->nation_recno != nation_recno );
		err_when( unitPtr->rank_id != RANK_KING && unitPtr->rank_id != RANK_GENERAL );

		if( unitPtr->nation_recno != nation_recno )
			continue;


		if( unitPtr->home_camp_firm_recno )
			continue;


		if( unitPtr->rank_id == RANK_KING && targetTown->nation_recno )
			continue;


		if( unitPtr->unit_mode == UNIT_MODE_OVERSEE )
		{
			firmPtr = firm_array[unitPtr->unit_mode_para];


			int j;
			for( j=firmPtr->linked_town_count-1 ; j>=0 ; j-- )
			{
				Town* townPtr = town_array[ firmPtr->linked_town_array[j] ];


				if( townPtr->nation_recno==0 &&
					 townPtr->average_target_resistance(nation_recno) <
					 townPtr->average_resistance(nation_recno) )
				{
					break;
				}
			}

			if( j>=0 )
				continue;
		}


		if( unitPtr->action_mode != ACTION_STOP ||
			 unitPtr->region_id() != targetTown->region_id )
		{
			continue;
		}


		err_when( unitPtr->skill.skill_id != SKILL_LEADING );

		targetResistance = 100-targetTown->camp_influence(unitPtr->sprite_recno);


		if( targetResistance < bestTargetResistance )
		{
			bestTargetResistance = targetResistance;
			bestUnitRecno = unitPtr->sprite_recno;
		}
	}

	return bestUnitRecno;
}
