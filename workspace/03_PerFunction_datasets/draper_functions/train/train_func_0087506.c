ai_create_new_trade(Firm* firmPtr, int stop1PickUpType, int stop2PickUpType)
{


	Nation* 		 ownNation = nation_array[nation_recno];
	UnitCaravan* unitCaravan;
	int			 rc, stop1Id, stop2Id;
	int			 caravanInRouteCount=0;

	for( int i=ownNation->ai_caravan_count-1 ; i>=0 ; i-- )
	{
		unitCaravan = (UnitCaravan*) unit_array[ ownNation->ai_caravan_array[i] ];

		err_when( unitCaravan->nation_recno != nation_recno );
		err_when( unitCaravan->unit_id != UNIT_CARAVAN );

		if( unitCaravan->stop_defined_num < 2 )
			continue;

		if( unitCaravan->stop_array[0].firm_recno == firm_recno &&
			 unitCaravan->stop_array[1].firm_recno == firmPtr->firm_recno )
		{
			stop1Id = 1;
			stop2Id = 2;
		}
		else if( unitCaravan->stop_array[1].firm_recno == firm_recno &&
					unitCaravan->stop_array[0].firm_recno == firmPtr->firm_recno )
		{
			stop1Id = 2;
			stop2Id = 1;
		}
		else
		{
			continue;
		}


		rc = 0;

		if( stop1PickUpType && !unitCaravan->has_pick_up_type(stop1Id, stop1PickUpType) )
		{
			if( unitCaravan->is_visible() )
				unitCaravan->set_stop_pick_up(stop1Id, stop1PickUpType, COMMAND_AI);
			rc = 1;
		}

		if( stop2PickUpType && !unitCaravan->has_pick_up_type(stop2Id, stop2PickUpType) )
		{
			if( unitCaravan->is_visible() )
				unitCaravan->set_stop_pick_up(stop2Id, stop2PickUpType, COMMAND_AI);
			rc = 1;
		}

		if( rc )
			return 1;

		caravanInRouteCount++;
	}

	if( caravanInRouteCount >= 2 )
		return 0;


	int unitRecno = hire_caravan(COMMAND_AI);

	if( !unitRecno )
		return 0;


	unitCaravan = (UnitCaravan*) unit_array[unitRecno];

	unitCaravan->set_stop(2, firmPtr->loc_x1, firmPtr->loc_y1, COMMAND_AI);

	err_when( unitCaravan->stop_array[0].firm_recno == firmPtr->firm_recno );

	unitCaravan->set_stop_pick_up(1, NO_PICK_UP, COMMAND_AI);
	unitCaravan->set_stop_pick_up(2, NO_PICK_UP, COMMAND_AI);

	if( stop1PickUpType )
		unitCaravan->set_stop_pick_up(1, stop1PickUpType, COMMAND_AI);

	if( stop2PickUpType )
		unitCaravan->set_stop_pick_up(2, stop2PickUpType, COMMAND_AI);

	return 1;
}
