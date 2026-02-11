process_game_chat_packet( ubyte *data, header *hinfo )
{
	int offset;
	ubyte mode;
	int color_index,player_index,to_player_index,should_display,server_msg;
	char msg[MULTI_MSG_MAX_TEXT_LEN+CALLSIGN_LEN+2];
	char expr[255];
	short from, to;

	offset = HEADER_LENGTH;


	GET_SHORT(from);


	GET_INT(server_msg);


	GET_DATA(mode);


	to = -1;
	switch(mode){
	case MULTI_MSG_TARGET:
		GET_SHORT(to);
		break;
	case MULTI_MSG_EXPR:
		GET_STRING(expr);
		break;
	}

	GET_STRING(msg);
	PACKET_SET_SIZE();


	color_index = find_player_id(from);
	player_index = color_index;


	if(player_index == -1){
		nprintf(("Network","Could not find player for processing game chat packet!\n"));
		return;
	}

	should_display = 0;


	if(Net_player->flags & NETINFO_FLAG_AM_MASTER){

		if(mode == MULTI_MSG_TARGET){
			to_player_index = find_player_id(to);
		} else {
			to_player_index = -1;
		}


		if(((to_player_index == -1) && (mode == MULTI_MSG_TARGET)) || (player_index == -1)){
			return;
		}


		if(Game_mode & GM_STANDALONE_SERVER){
			should_display = 1;
		}

		else {
			if((mode == MULTI_MSG_ALL) ||
				((mode == MULTI_MSG_FRIENDLY) && (Net_player->p_info.team == Net_players[player_index].p_info.team)) ||
				((mode == MULTI_MSG_HOSTILE) && (Net_player->p_info.team != Net_players[player_index].p_info.team)) ||
				((mode == MULTI_MSG_TARGET) && (MY_NET_PLAYER_NUM == to_player_index)) ||
				((mode == MULTI_MSG_EXPR) && multi_msg_matches_expr(Net_player,expr)) ){
				should_display = 1;
			}
		}


		switch(mode){

		case MULTI_MSG_TARGET:

			if(to_player_index != MY_NET_PLAYER_NUM){
				send_game_chat_packet(&Net_players[player_index], msg, (int)mode, &Net_players[to_player_index], NULL, server_msg);
			}
			break;

		case MULTI_MSG_EXPR:
			send_game_chat_packet(&Net_players[player_index], msg, (int)mode, NULL, expr, server_msg);
			break;

		default :
			send_game_chat_packet(&Net_players[player_index], msg, (int)mode, NULL, NULL, server_msg);
			break;
		}
	}

	else {
		should_display = 1;
	}


	if(should_display){
		if(server_msg == 2){
			HUD_printf(msg);
		} else {
			multi_display_chat_msg(msg, player_index, !server_msg);
		}
	}
}
