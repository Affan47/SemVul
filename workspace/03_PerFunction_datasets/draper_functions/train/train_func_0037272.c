run_main_menu_option(int optionId)
{


	if( optionId==1 )
	{
		single_player_menu();
	}


	if( optionId==2 )
	{
#ifndef DISABLE_MULTI_PLAYER
		game_mode = GAME_MULTI_PLAYER;
		multi_player_menu(0, NULL);

#endif
	}


	if( optionId==3 )
	{
		game_mode = GAME_ENCYCLOPEDIA;
		view_encyclopedia();
	}


	if( optionId==4 )
	{
		game_file_array.disp_hall_of_fame();
	}


	if( optionId==5 )
	{
		if( misc.is_file_exist("TESTING2.SYS") )
		{
			game_mode = GAME_TEST;
			test_game();
		}
		else
		{
			game_mode = GAME_CREDITS;
			view_credits();
		}
	}


	if( optionId==6 )
	{
		sys.signal_exit_flag = 1;
	}

}
