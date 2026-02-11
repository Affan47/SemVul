multi_find_player_by_callsign(char *callsign)
{
	int idx;
	for(idx=0;idx<MAX_PLAYERS;idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && (strcmp(callsign,Net_players[idx].m_player->callsign)==0)){
			return idx;
		}
	}

	return -1;
}
