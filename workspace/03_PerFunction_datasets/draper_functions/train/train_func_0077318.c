think_trade()
{


	Nation*     ownNation  = nation_array[nation_recno];
	UnitMarine* unitMarine = ai_get_free_trade_ship();

	if( !unitMarine )
		return 0;


	if( total_linked_trade_firm() == 0 )
		return 0;


	Firm* 		firmPtr;
	FirmHarbor* firmHarbor;

	int i;
	for( i=firm_array.size() ; i>0 ; i-- )
	{
		if( firm_array.is_deleted(i) )
			continue;

		firmPtr = firm_array[i];


		if(firmPtr->firm_id!=FIRM_HARBOR)
			continue;


		firmHarbor = (FirmHarbor*) firmPtr;

		if( firmHarbor->total_linked_trade_firm() == 0 )
			continue;

		if( !ownNation->has_trade_ship(firm_recno, i) )
			break;
	}

	if( i==0 )
		return 0;


	unitMarine->set_stop( 1, loc_x1, loc_y1, COMMAND_AI);
	unitMarine->set_stop( 2, firmHarbor->loc_x1, firmHarbor->loc_y1, COMMAND_AI);

	unitMarine->set_stop_pick_up(1, AUTO_PICK_UP, COMMAND_AI);
	unitMarine->set_stop_pick_up(2, AUTO_PICK_UP, COMMAND_AI);

	return 1;
}
