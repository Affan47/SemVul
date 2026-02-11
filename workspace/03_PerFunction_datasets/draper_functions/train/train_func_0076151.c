player_select_scroll_list_down()
{

	if ( Player_select_pilot < Player_select_num_pilots - 1 ) {
		Player_select_pilot++;
		gamesnd_play_iface(SND_SCROLL);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}

	if ( Player_select_pilot >= (Player_select_list_start + Max_lines) ) {
		Player_select_list_start++;
	}
}
