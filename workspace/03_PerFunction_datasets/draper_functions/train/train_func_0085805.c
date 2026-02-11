think_capture_target_town()
{
	if( !linked_town_count || !overseer_recno )
		return 0;


	if( nation_array[nation_recno]->is_action_exist( loc_x1, loc_y1, -1, -1, ACTION_AI_ASSIGN_WORKER, FIRM_CAMP ) )
		return 0;


	int	curResistance, curTargetResistance, resistanceDec;
	int 	i, minResistance=100, bestTownRecno=0;
	Town* townPtr;
	int   prefPeacefulness = nation_array[nation_recno]->pref_peacefulness;
	Nation* ownNation = nation_array[nation_recno];
	int   overseerRaceId = unit_array[overseer_recno]->race_id;

	for( i=0 ; i<linked_town_count ; i++ )
	{
		townPtr = town_array[ linked_town_array[i] ];

		if( townPtr->nation_recno == nation_recno )
			continue;


		if( !townPtr->nation_recno )
		{
			curResistance = townPtr->average_resistance(nation_recno);
			curTargetResistance = townPtr->average_target_resistance(nation_recno);

			resistanceDec = curResistance - curTargetResistance;


			if( resistanceDec > 0 &&
				 curResistance > 25-25*ownNation->pref_peacefulness/100 &&
				 townPtr->race_pop_array[overseerRaceId-1] >= 5 )
			{
				continue;
			}
		}
		else
		{
			NationRelation* nationRelation = ownNation->get_relation(townPtr->nation_recno);

			if( nationRelation->status != NATION_HOSTILE )
				continue;

			curResistance = townPtr->average_loyalty();
		}


		if( curResistance < minResistance )
		{
			minResistance = curResistance;
			bestTownRecno = townPtr->town_recno;
		}
	}

	return bestTownRecno;
}
