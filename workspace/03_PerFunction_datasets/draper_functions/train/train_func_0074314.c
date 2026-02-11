multi_num_observers()
{
	int idx,count;


	count = 0;
	for(idx=0;idx<MAX_PLAYERS;idx++){

		if(MULTI_CONNECTED(Net_players[idx]) && MULTI_PERM_OBSERVER(Net_players[idx])){
			count++;
		}
	}

	return count;

}
