multi_ts_blit_wings()
{
	int idx;


	for(idx=0;idx<MAX_WSS_SLOTS;idx++){

		if(Multi_ts_team[Net_player->p_info.team].multi_ts_flag[idx] == MULTI_TS_FLAG_NONE){
			continue;
		}


		if(Multi_ts_team[Net_player->p_info.team].multi_ts_flag[idx] == MULTI_TS_FLAG_EMPTY){
			ss_blit_ship_icon(Multi_ts_slot_icon_coords[idx][gr_screen.res][MULTI_TS_X_COORD],Multi_ts_slot_icon_coords[idx][gr_screen.res][MULTI_TS_Y_COORD],-1,0);
		} else {
			ss_blit_ship_icon(Multi_ts_slot_icon_coords[idx][gr_screen.res][MULTI_TS_X_COORD],Multi_ts_slot_icon_coords[idx][gr_screen.res][MULTI_TS_Y_COORD],Wss_slots[idx].ship_class,multi_ts_slot_bmap_num(idx));


			if((Netgame.type_flags & NG_TYPE_TEAM) && (Multi_ts_team[Net_player->p_info.team].multi_ts_player[idx] != NULL) && (Multi_ts_team[Net_player->p_info.team].multi_ts_player[idx]->flags & NETINFO_FLAG_TEAM_CAPTAIN)){
				gr_set_color_fast(&Color_bright);
				gr_string(Multi_ts_slot_icon_coords[idx][gr_screen.res][MULTI_TS_X_COORD] - 5,Multi_ts_slot_icon_coords[idx][gr_screen.res][MULTI_TS_Y_COORD] - 5, XSTR("C",737));
			}
		}
	}
}
