multi_df_setup_kill_matrix()
{
	int idx, s_idx;
	multi_df_score *s;

	Multi_df_score_count = 0;


	for(idx=0; idx<MAX_PLAYERS; idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_PERM_OBSERVER(Net_players[idx]) && (Net_players[idx].m_player != NULL)){

			s = &Multi_df_score[Multi_df_score_count++];

			ml_printf("Dogfight debrief stats for %s", Net_players[idx].m_player->callsign);
			for(s_idx=0; s_idx<MAX_PLAYERS; s_idx++){
				ml_printf("%d", Net_players[idx].m_player->stats.m_dogfight_kills[s_idx]);
			}

			s->stats = Net_players[idx].m_player->stats;
			strcpy_s(s->callsign, Net_players[idx].m_player->callsign);
			s->np_index = idx;
		}
	}
}
