process_ship_status_packet(ubyte *data, header *hinfo)
{
   int idx;
	int offset;
	int player_num,unique_id;
	button_info bi;
	int i_tmp;

	offset = HEADER_LENGTH;


	memset(&bi,0,sizeof(button_info));


	GET_INT(unique_id);

	for(idx=0;idx<NUM_BUTTON_FIELDS;idx++){
		GET_INT(i_tmp);
		bi.status[idx] = i_tmp;
	}

	PACKET_SET_SIZE();


	if(Net_player->flags & NETINFO_FLAG_AM_MASTER){

		player_num = find_player_id(hinfo->id);
		Assert(player_num >= 0);
		if(player_num < 0){
			return;
		}


		if(!MULTI_OBSERVER(Net_players[player_num]) && !lookup_ship_status(&Net_players[player_num],unique_id)){


			send_ship_status_packet(&Net_players[player_num], &bi,unique_id);


			multi_apply_ship_status(&Net_players[player_num], &bi, 0);
		}

	} else {


		multi_apply_ship_status(Net_player, &bi, 1);

	}
}
