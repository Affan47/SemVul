multi_df_debrief_close()
{
	int idx;


	chatbox_close();


	if (multi_debrief_stats_accept_code() != 1) {

		if (multi_debrief_stats_accept_code() != 1) {
			if(MULTIPLAYER_MASTER){
				for(idx=0; idx<MAX_PLAYERS; idx++){
					if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_PERM_OBSERVER(Net_players[idx]) && (Net_players[idx].m_player != NULL)){
						scoring_backout_accept(&Net_players[idx].m_player->stats);
					}
				}
			} else {
				scoring_backout_accept( &Player->stats );
			}
		}
	}


	common_music_close();
}
