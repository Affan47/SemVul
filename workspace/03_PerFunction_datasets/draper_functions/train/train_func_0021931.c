send_accept_packet(int new_player_num, int code, int ingame_join_team)
{
	int packet_size, i;
	ubyte data[MAX_PACKET_SIZE],val;
	char notify_string[256];


	Assert(new_player_num >= 0);


	Net_players[new_player_num].last_heard_time = timer_get_fixed_seconds();


	packet_size = 0;
	BUILD_HEADER(ACCEPT);


	ADD_INT(code);


	if (code & ACCEPT_INGAME) {

		ADD_STRING(Game_current_mission_filename);


		if(ingame_join_team != -1){
			val = 1;
			ADD_DATA(val);
			val = (ubyte)ingame_join_team;
			ADD_DATA(val);
		} else {
			val = 0;
			ADD_DATA(val);
		}
	}

	if (code & ACCEPT_OBSERVER) {
		Assert(!(code & (ACCEPT_CLIENT | ACCEPT_HOST)));
	}

	if (code & ACCEPT_HOST) {
		Assert(!(code & (ACCEPT_CLIENT | ACCEPT_OBSERVER | ACCEPT_INGAME)));
	}

	if (code & ACCEPT_CLIENT) {
		Assert(!(code & (ACCEPT_HOST | ACCEPT_OBSERVER | ACCEPT_INGAME)));
	}


	if (Game_skill_level < 0 || Game_skill_level >= NUM_SKILL_LEVELS) {
		Warning(LOCATION, "Trying to send packet containing invalid skill level %i! Valid range 0 to %i. Resetting to default.", Game_skill_level, NUM_SKILL_LEVELS);
		Game_skill_level = game_get_default_skill_level();
	}
	ADD_INT(Game_skill_level);


	ADD_INT(new_player_num);


	ADD_SHORT(Net_players[new_player_num].player_id);


	ADD_INT(Netgame.type_flags);


	psnet_send(&Net_players[new_player_num].p_info.addr, data, packet_size);


	for (i=0; i<MAX_PLAYERS; i++) {

		if ( !MULTI_CONNECTED(Net_players[i]) || psnet_same(&Net_players[new_player_num].p_info.addr, &(Net_players[i].p_info.addr)) || (Net_player == &Net_players[i])) {
			continue;
		}


		send_new_player_packet(new_player_num,&Net_players[i]);
	}


	if(Net_players[new_player_num].m_player->callsign != NULL){
		sprintf(notify_string,XSTR("<%s has joined>",717), Net_players[new_player_num].m_player->callsign);
		multi_display_chat_msg(notify_string, 0, 0);
	}


	if (!(code & ACCEPT_OBSERVER)) {
		multi_team_handle_join(&Net_players[new_player_num]);
	}


	if(Net_players[new_player_num].tracker_player_id >= 0){
		ml_printf(NOX("Server accepted %s (tracker id %d) as new client"), Net_players[new_player_num].m_player->callsign, Net_players[new_player_num].tracker_player_id);
	} else {
		ml_printf(NOX("Server accepted %s as new client"), Net_players[new_player_num].m_player->callsign);
	}
}
