find_player_id(short player_id)
{
	int i;
	for (i = 0; i < MAX_PLAYERS; i++ ) {
		if ( !MULTI_CONNECTED(Net_players[i])){
			continue;
		}
		if(player_id == Net_players[i].player_id){
			return i;
		}
	}


	return -1;
}
