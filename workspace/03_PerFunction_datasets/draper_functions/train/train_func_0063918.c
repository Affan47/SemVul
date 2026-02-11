next_day()
{


	Firm::next_day();


	recruit_worker();


	update_worker();


	if( info.game_date%PROCESS_GOODS_INTERVAL == firm_recno%PROCESS_GOODS_INTERVAL )
	{
		produce_raw();
		set_next_output_firm();
	}
}
