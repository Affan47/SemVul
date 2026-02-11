send_wss_slots_data_packet(int team_num,int final,net_player *p,int std_request)
{
	ubyte data[MAX_PACKET_SIZE],val;
	short val_short;
	int idx,i;
	int packet_size = 0;


	BUILD_HEADER(WSS_SLOTS_DATA);


	val = (ubyte)std_request;
	ADD_DATA(val);


	val = (ubyte)team_num;
	ADD_DATA(val);


	val = (ubyte)final;
	ADD_DATA(val);


	if((Game_mode & GM_STANDALONE_SERVER) && std_request){

		multi_io_send_reliable(Netgame.host, data, packet_size);
		return;
	}


	for(idx=0;idx<MULTI_TS_NUM_SHIP_SLOTS;idx++){

		val = (ubyte)Wss_slots_teams[team_num][idx].ship_class;
		ADD_DATA(val);


		for(i = 0;i<MAX_SHIP_WEAPONS;i++){
			val_short = (short)Wss_slots_teams[team_num][idx].wep[i];
			ADD_SHORT(val_short);
		}


		for(i = 0;i<MAX_SHIP_WEAPONS;i++){
			val_short = (short)Wss_slots_teams[team_num][idx].wep_count[i];
			ADD_SHORT(val_short);
		}
	}


	if(Net_player->flags & NETINFO_FLAG_GAME_HOST){
 		if(Net_player->flags & NETINFO_FLAG_AM_MASTER){

			if(p == NULL){
				multi_io_send_to_all_reliable(data, packet_size);
			}

			else {
				multi_io_send_reliable(p, data, packet_size);
			}
		} else {
			multi_io_send_reliable(Net_player, data, packet_size);
		}
	}

	else {

		if(p == NULL){
			multi_io_send_to_all_reliable(data, packet_size);
		}

		else {
			multi_io_send_reliable(p, data, packet_size);
		}
	}
}
