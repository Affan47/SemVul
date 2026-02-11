think_build_market()
{
	if( no_neighbor_space )
		return 0;

	Nation* nationPtr = nation_array[nation_recno];


	if( stock_qty < max_stock_qty * 0.2 )
		return 0;


	if( !nationPtr->can_ai_build(FIRM_MARKET) )
		return 0;


	FirmMarket* firmPtr;

	for(int i=0; i<linked_firm_count; i++)
	{
		err_when(!linked_firm_array[i] || firm_array.is_deleted(linked_firm_array[i]));

		firmPtr = (FirmMarket*) firm_array[linked_firm_array[i]];

		if(firmPtr->firm_id!=FIRM_MARKET)
			continue;


		if( firmPtr->nation_recno == nation_recno &&
			 ((FirmMarket*)firmPtr)->is_retail_market==0 )
		{
			return 0;
		}
	}


	short buildXLoc, buildYLoc;

	if( !nationPtr->find_best_firm_loc(FIRM_MARKET, loc_x1, loc_y1, buildXLoc, buildYLoc) )
	{
		no_neighbor_space = 1;
		return 0;
	}

	nationPtr->add_action(buildXLoc, buildYLoc, loc_x1, loc_y1, ACTION_AI_BUILD_FIRM, FIRM_MARKET);

	return 1;
}
