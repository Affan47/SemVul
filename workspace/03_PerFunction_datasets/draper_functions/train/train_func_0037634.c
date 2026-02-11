escort_compare_func(const void *e1, const void *e2)
{
	escort_info *escort1, *escort2;
	int diff;
	int ret;

	escort1 = (escort_info*) e1;
	escort2 = (escort_info*) e2;


	if(MULTI_DOGFIGHT){
		int n1, n2;

		n1 = find_player_id(escort1->np_id);
		n2 = find_player_id(escort2->np_id);
		if((n1 < 0) || (n2 < 0) || (Net_players[n1].m_player == NULL) || (Net_players[n2].m_player == NULL)){
			ret = 0;
		} else {

			if(Net_players[n1].m_player->stats.m_kill_count_ok >= Net_players[n2].m_player->stats.m_kill_count_ok){
				ret = -1;
			} else {
				ret = 1;
			}
		}
	} else {
		diff = escort2->priority - escort1->priority;

		if (diff != 0) {
			ret = diff;
		} else {
			char *name1, *name2;
			name1 = Ships[Objects[escort1->objnum].instance].ship_name;
			name2 = Ships[Objects[escort2->objnum].instance].ship_name;

			ret = stricmp(name1, name2);
		}
	}

	return ret;
}
