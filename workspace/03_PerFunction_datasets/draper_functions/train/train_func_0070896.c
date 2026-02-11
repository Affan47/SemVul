think_attack_linked_enemy()
{
	Firm*   firmPtr;
	Nation* ownNation = nation_array[nation_recno];
	int	  targetCombatLevel;

	for(int i=0; i<linked_firm_count; i++)
	{
		if( linked_firm_enable_array[i] != LINK_EE )
			continue;

		firmPtr = firm_array[ linked_firm_array[i] ];

		if( firmPtr->nation_recno == nation_recno )
			continue;

		if( firmPtr->should_close_flag )
			continue;


		if( firmPtr->firm_ai &&
			 ownNation->get_relation_status(firmPtr->nation_recno) != NATION_HOSTILE )
		{
			continue;
		}


		if( firmPtr->firm_id == FIRM_CAMP )
		{


			int nationStatus = ownNation->get_relation_status(firmPtr->nation_recno);

			if( nationStatus >= NATION_FRIENDLY )
			{
				if( !ownNation->ai_should_attack_friendly(firmPtr->nation_recno, 100) )
					continue;

				ownNation->ai_end_treaty(firmPtr->nation_recno);
			}
			else if( nationStatus == NATION_NEUTRAL )
			{


				if( nation_array[firmPtr->nation_recno]->military_rank_rating() >
					 ownNation->military_rank_rating() )
				{
					continue;
				}
			}


			int tradeRating = ownNation->trade_rating(firmPtr->nation_recno);

			if( tradeRating > 50 ||
				 tradeRating + ownNation->ai_trade_with_rating(firmPtr->nation_recno) > 100 )
			{
				continue;
			}

			targetCombatLevel = ((FirmCamp*)firmPtr)->total_combat_level();
		}
		else
		{


			if( ownNation->get_relation_status(firmPtr->nation_recno) != NATION_HOSTILE )
				continue;

			targetCombatLevel = 50;
		}


		ownNation->ai_attack_target( firmPtr->loc_x1, firmPtr->loc_y1, targetCombatLevel );

		return 1;
	}

	return 0;
}
