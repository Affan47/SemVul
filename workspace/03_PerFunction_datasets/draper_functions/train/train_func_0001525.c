process_ai()
{


	if( !tech_id )
		think_new_research();


	if( info.game_date%15==firm_recno%15 )
	{
		if( worker_count < MAX_WORKER )
			ai_recruit_worker();
	}


	if( info.game_date%30==firm_recno%30 )
	{
		if( think_del() )
			return;
	}
}
