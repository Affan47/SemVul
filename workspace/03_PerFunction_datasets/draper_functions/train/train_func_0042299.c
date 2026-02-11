multi_ts_init_flags()
{
	int idx,s_idx;


	for(idx=0;idx<MULTI_TS_MAX_TVT_TEAMS;idx++){
		for(s_idx=0;s_idx<MULTI_TS_NUM_SHIP_SLOTS;s_idx++){
			Multi_ts_team[idx].multi_ts_flag[s_idx] = MULTI_TS_FLAG_NONE;
		}
	}


	if(Netgame.type_flags & NG_TYPE_TEAM){
		for(idx=0;idx<MULTI_TS_MAX_TVT_TEAMS;idx++){
			for(s_idx=0;s_idx<MULTI_TS_NUM_SHIP_SLOTS_TEAM;s_idx++){

				if((Multi_ts_team[idx].multi_ts_objnum[s_idx] != -1) && (Wss_slots_teams[idx][s_idx].ship_class == -1)){
					Multi_ts_team[idx].multi_ts_flag[s_idx] = MULTI_TS_FLAG_EMPTY;
				} else if((Multi_ts_team[idx].multi_ts_objnum[s_idx] != -1) && (Wss_slots_teams[idx][s_idx].ship_class != -1)){
					Multi_ts_team[idx].multi_ts_flag[s_idx] = Wss_slots_teams[idx][s_idx].ship_class;
				}
			}
		}
	}

	else {
		for(idx=0;idx<MULTI_TS_NUM_SHIP_SLOTS;idx++){

			if((Multi_ts_team[0].multi_ts_objnum[idx] != -1) && (Wss_slots[idx].ship_class == -1)){
				Multi_ts_team[0].multi_ts_flag[idx] = MULTI_TS_FLAG_EMPTY;
			} else if((Multi_ts_team[0].multi_ts_objnum[idx] != -1) && (Wss_slots[idx].ship_class != -1)){
				Multi_ts_team[0].multi_ts_flag[idx] = Wss_slots[idx].ship_class;
			}
		}
	}
}
