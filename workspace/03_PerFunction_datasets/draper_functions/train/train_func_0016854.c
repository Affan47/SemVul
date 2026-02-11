create_default_player_ship(int use_last_flown)
{
	int	player_ship_class=-1, i;


	if ( use_last_flown ) {
		player_ship_class = Players[Player_num].last_ship_flown_si_index;
	}
	else {
		for (i = 0; i < Num_ship_classes; i++) {
			if ( !stricmp(Ship_info[i].name, default_player_ship) ) {
				player_ship_class = i;
				Players[Player_num].last_ship_flown_si_index = player_ship_class;
				break;
			}
		}

		if (i == Num_ship_classes)
			return 1;
	}


	if (player_ship_class == -1) {
		popup(PF_TITLE_BIG | PF_TITLE_RED | PF_USE_AFFIRMATIVE_ICON | PF_NO_NETWORKING, 1, POPUP_OK, XSTR("Error!\n\nCannot find "
			"a valid last flown ship\n\nHave you played any missions since activating this mod/campaign?", 1619));
		return 1;
	} else {
		update_player_ship(player_ship_class);
	}


#ifndef NDEBUG
	if ( use_descent ) {
		use_descent = 0;
		toggle_player_object();
	}
#endif

	return 0;
}
