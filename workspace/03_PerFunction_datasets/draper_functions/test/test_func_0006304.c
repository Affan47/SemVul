deinit_derived()
{
	if( sys.signal_exit_flag )
		return;


	int loopCount=0;

	if( monster_king.monster_id )
		mobilize_king();

	while( monster_general_count > 0 )
	{
		if(!mobilize_general(1))
			break;

		err_when( loopCount++ > 100 );
	}

	clear_defense_mode();
}
