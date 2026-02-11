multi_find_player_by_ship_name(char *ship_name, bool inc_respawning)
{
	int idx;
	p_object *p_objp;


	if(ship_name == NULL){
		return -1;
	}

	for(idx=0; idx<MAX_PLAYERS; idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_OBSERVER(Net_players[idx]) && (Net_players[idx].m_player != NULL) && (Net_players[idx].m_player->objnum >= 0) && (Net_players[idx].m_player->objnum < MAX_OBJECTS) && (Objects[Net_players[idx].m_player->objnum].type == OBJ_SHIP) &&
			(Objects[Net_players[idx].m_player->objnum].instance >= 0) && (Objects[Net_players[idx].m_player->objnum].instance < MAX_SHIPS) && !stricmp(ship_name, Ships[Objects[Net_players[idx].m_player->objnum].instance].ship_name) ){
			return idx;
		}
	}

	if (inc_respawning) {
		p_objp = mission_parse_get_arrival_ship(ship_name);
		idx = multi_find_player_by_parse_object(p_objp);

		if((idx >= 0) && (idx < MAX_PLAYERS)){
			return idx;
		}
	}

	return -1;
}
