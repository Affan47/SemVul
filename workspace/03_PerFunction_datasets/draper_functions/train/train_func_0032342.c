deinit()
{
	if( nation_recno==0 )
		return;


	talk_res.del_all_nation_msg(nation_recno);


	close_all_firm();


	Town* townPtr;

	int i;
	for( i=town_array.size() ; i>0 ; i-- )
	{
		if( town_array.is_deleted(i) )
			continue;

		townPtr = town_array[i];

		if( townPtr->nation_recno == nation_recno )
			townPtr->set_nation(0);
	}


	for( i=spy_array.size() ; i>0 ; i-- )
	{
		if( spy_array.is_deleted(i) )
			continue;

		Spy* spyPtr = spy_array[i];


		if( spyPtr->true_nation_recno == nation_recno )
			spyPtr->drop_spy_identity();


		else if( spyPtr->cloaked_nation_recno == nation_recno )
			spyPtr->change_cloaked_nation(spyPtr->true_nation_recno);

		err_when( spyPtr->true_nation_recno == nation_recno ||
				    spyPtr->cloaked_nation_recno == nation_recno );
	}


	deinit_all_unit();


	if( !sys.signal_exit_flag )
	{
		if( info.default_viewing_nation_recno == nation_recno )
		{
			info.default_viewing_nation_recno = nation_array.player_recno;
			sys.set_view_mode(MODE_NORMAL);
		}

		else if( info.viewing_nation_recno == nation_recno )
			sys.set_view_mode(MODE_NORMAL);


		if( nation_recno == nation_array.player_recno )
		{
			sys.disp_view_mode(1);
		}

	}

	nation_recno = 0;
}
