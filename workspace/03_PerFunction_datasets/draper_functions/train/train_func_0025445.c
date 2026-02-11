process_ai()
{


	if( !raw_id || reserve_qty==0 )
	{
		err_when( under_construction );

		ai_del_firm();
		return;
	}


	if( info.game_date%15==firm_recno%15 )
	{
		if( worker_count < MAX_WORKER )
			ai_recruit_worker();
	}


	int rc = info.game_date%30==firm_recno%30;

	if( nation_array[nation_recno]->ai_factory_count==0 )
		rc = info.game_date%5==firm_recno%5;

	if( rc )
	{
		if( !think_build_factory(raw_id) )
			ai_should_build_factory_count = 0;

  		think_build_market();
	}


	if( info.game_date%30==firm_recno%30 )
		think_inc_productivity();
}
