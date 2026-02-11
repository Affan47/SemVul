think_build_factory(int rawId)
{
	if( no_neighbor_space )
		return 0;

	Nation* nationPtr = nation_array[nation_recno];


	if( !nationPtr->can_ai_build(FIRM_FACTORY) )
		return 0;


	int 			 factoryCount=0;
	FirmFactory* firmPtr;
	Firm*			 firmMarket;

	for(int i=0; i<linked_firm_count; i++)
	{
		err_when(!linked_firm_array[i] || firm_array.is_deleted(linked_firm_array[i]));

		firmPtr = (FirmFactory*) firm_array[linked_firm_array[i]];

		if(firmPtr->firm_id!=FIRM_FACTORY)
			continue;

		if( firmPtr->nation_recno != nation_recno )
			continue;

		if( firmPtr->product_raw_id != rawId )
			continue;


		if( firmPtr->worker_count < MAX_WORKER )
			return 0;


		if( firmPtr->stock_qty > firmPtr->max_stock_qty * 0.1 )
			return 0;


		for( int j=firmPtr->linked_firm_count-1 ; j>=0 ; j-- )
		{
			if( firmPtr->linked_firm_enable_array[j] != LINK_EE )
				continue;

			firmMarket = firm_array[ firmPtr->linked_firm_array[j] ];

			if( firmMarket->firm_id != FIRM_MARKET )
				continue;


			MarketGoods *marketGoods = ((FirmMarket*)firmMarket)->market_product_array[rawId-1];

			if( marketGoods && marketGoods->stock_qty > 100 )
				return 0;
		}


		factoryCount++;
	}


	if( factoryCount>=1 && !nationPtr->ai_has_enough_food() )
		return 0;


	if( firm_id == FIRM_MINE )
	{
		if( ((FirmMine*)this)->reserve_qty < 1000 && factoryCount>=1 )
			return 0;
	}


	if( nationPtr->total_jobless_population < factoryCount * MAX_WORKER )
		return 0;


	if( ++ai_should_build_factory_count >= 3 )
	{
		short buildXLoc, buildYLoc;

		if( !nationPtr->find_best_firm_loc(FIRM_FACTORY, loc_x1, loc_y1, buildXLoc, buildYLoc) )
		{
			no_neighbor_space = 1;
			return 0;
		}

		nationPtr->add_action(buildXLoc, buildYLoc, loc_x1, loc_y1, ACTION_AI_BUILD_FIRM, FIRM_FACTORY);

		ai_should_build_factory_count = 0;
	}

	return 1;
}
