multi_voice_process_packet(ubyte *data, header *hinfo)
{
	ubyte code,msg_mode;
	ushort target_sig;
	int player_index,stream_index,target_index;
	int offset = HEADER_LENGTH;


	player_index = find_player_id(hinfo->id);


	GET_DATA(code);


	switch(code){

	case MV_CODE_TAKE_TOKEN:

		if(!Multi_voice_can_record){
			Int3();
		}

		Multi_voice_token = 0;
		break;


	case MV_CODE_DENY_TOKEN:

		Multi_voice_denied_stamp = timestamp(MULTI_VOICE_DENIED_TIME);
		break;


	case MV_CODE_GIVE_TOKEN:
		GET_DATA(Multi_voice_stream_id);


		if(!Multi_voice_can_record){
			Int3();
		}


		if(!Multi_voice_keydown){
			multi_voice_release_token();
		} else {
			Multi_voice_token = 1;
		}
		break;


	case MV_CODE_REQUEST_TOKEN:
		if(player_index >= 0){
			multi_voice_process_token_request(player_index);
		}
		break;


	case MV_CODE_RELEASE_TOKEN:
		if(player_index >= 0){
			stream_index = multi_voice_find_token(player_index);
		} else {
			break;
		}

		if(stream_index >= 0){

			Multi_voice_stream[stream_index].token_status = MULTI_VOICE_TOKEN_INDEX_RELEASED;


			Net_players[player_index].s_info.voice_token_timestamp = timestamp(Netgame.options.voice_token_wait);
		}
		break;


	case MV_CODE_PLAYER_PREFS:
		Assert(player_index != -1);
		offset += multi_voice_process_player_prefs(data+offset,player_index);
		break;


	case MV_CODE_DATA:
#ifdef MULTI_VOICE_VERBOSE
		nprintf(("Network","VOICE : PROC DATA\n"));
#endif

		target_index = -1;
		GET_DATA(msg_mode);
		if(msg_mode == MULTI_MSG_TARGET){
			GET_USHORT(target_sig);
			target_index = multi_find_player_by_net_signature(target_sig);
			Assert(target_index != -1);
		}

		offset += multi_voice_process_data(data+offset,player_index,msg_mode,(target_index == -1) ? NULL : &Net_players[target_index]);


		if(Net_player->flags & NETINFO_FLAG_AM_MASTER){
			multi_voice_route_data(data,offset,player_index,msg_mode,(target_index == -1) ? NULL : &Net_players[target_index]);
		}
		break;


	case MV_CODE_DATA_DUMMY:
#ifdef MULTI_VOICE_VERBOSE
		nprintf(("Network","VOICE : PROC DATA DUMMY\n"));
#endif

		target_index = -1;
		GET_DATA(msg_mode);
		if(msg_mode == MULTI_MSG_TARGET){
			GET_USHORT(target_sig);
			target_index = multi_find_player_by_net_signature(target_sig);
			Assert(target_index != -1);
		}

		offset += multi_voice_process_data_dummy(data+offset);


		if(Net_player->flags & NETINFO_FLAG_AM_MASTER){
			multi_voice_route_data(data,offset,player_index,msg_mode,(target_index == -1) ? NULL : &Net_players[target_index]);
		}
		break;
	}
	PACKET_SET_SIZE();
}
