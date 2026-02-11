mobilize_capturer(int unitRecno)
{


	Unit* unitPtr = unit_array[unitRecno];

	if( unitPtr->unit_mode == UNIT_MODE_OVERSEE )
	{
		Firm* firmPtr = firm_array[unitPtr->unit_mode_para];
		Town* townPtr;


		int i;
		for( i=0 ; i<firmPtr->linked_town_count ; i++ )
		{
			townPtr = town_array[ firmPtr->linked_town_array[i] ];

			if( townPtr->nation_recno != nation_recno )
				continue;


			int unitRecno = townPtr->recruit( SKILL_LEADING, firmPtr->majority_race(), COMMAND_AI );


			if( !unitRecno )
				unitRecno = townPtr->recruit( SKILL_LEADING, townPtr->majority_race(), COMMAND_AI );

			if( unitRecno )
			{
				add_action(townPtr->loc_x1, townPtr->loc_y1, -1, -1, ACTION_AI_ASSIGN_OVERSEER, FIRM_CAMP);
				break;
			}
		}

		if( i==firmPtr->linked_town_count )
			return 0;


		firmPtr->mobilize_overseer();
	}

	return 1;
}
