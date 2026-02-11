multi_pxo_scroll_players_down()
{
	player_list *lookup;
	int count = 0;


	lookup = Multi_pxo_player_start;
	if(lookup == NULL ){
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}
	count = 0;
	while(lookup->next != Multi_pxo_players){
		lookup = lookup->next;
		count++;
	}


	if(count >= Multi_pxo_max_player_display[gr_screen.res]){
		Multi_pxo_player_start = Multi_pxo_player_start->next;
		gamesnd_play_iface(SND_USER_SELECT);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
}
