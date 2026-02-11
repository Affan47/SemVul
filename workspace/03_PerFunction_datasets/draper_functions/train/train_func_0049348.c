init_derived()
{


	Location* locPtr = scan_raw_site();

	if( locPtr )
	{
		site_recno  = locPtr->site_recno();
		raw_id		= site_array[site_recno]->object_id;
		reserve_qty = (float) site_array[site_recno]->reserve_qty;

		site_array[site_recno]->has_mine = 1;
		site_array.untapped_raw_count--;

		err_when( site_array.untapped_raw_count < 0 );
	}
	else
	{
		site_recno 	= 0;
		raw_id 		= 0;
		reserve_qty = (float) 0;
	}

	stock_qty 	 	= (float) 0;
	max_stock_qty  = (float) DEFAULT_MINE_MAX_STOCK_QTY;


	if( raw_id )
		nation_array[nation_recno]->raw_count_array[raw_id-1]++;
}
