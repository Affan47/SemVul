multi_team_sync_captains()
{
	int idx;
	int team0_cap,team1_cap;


	if(!MULTIPLAYER_MASTER){
		return;
	}


	team0_cap = 0;
	team1_cap = 0;
	for(idx=0;idx<MAX_PLAYERS;idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_PERM_OBSERVER(Net_players[idx]) && (Net_players[idx].flags & NETINFO_FLAG_TEAM_CAPTAIN)){
			switch(Net_players[idx].p_info.team){
			case 0 :
				team0_cap = 1;
				break;
			case 1 :
				team1_cap = 1;
				break;
			}
		}
	}


	if(!team0_cap){
		for(idx=0;idx<MAX_PLAYERS;idx++){
			if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_PERM_OBSERVER(Net_players[idx]) && (Net_players[idx].p_info.team == 0) && !(Net_players[idx].flags & NETINFO_FLAG_TEAM_CAPTAIN)){
				multi_team_set_captain(&Net_players[idx],1);
				break;
			}
		}
	}


	if(!team1_cap){
		for(idx=0;idx<MAX_PLAYERS;idx++){
			if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && !MULTI_PERM_OBSERVER(Net_players[idx]) && (Net_players[idx].p_info.team == 1) && !(Net_players[idx].flags & NETINFO_FLAG_TEAM_CAPTAIN)){
				multi_team_set_captain(&Net_players[idx],1);
				break;
			}
		}
	}
}
