multi_voice_player_send_stream()
{
	ubyte data[MAX_PACKET_SIZE],code,*rbuf,msg_mode,chunk_index;
	ushort chunk_size,uc_size;
	int packet_size = 0;
	int sound_size,size_sent,target_index,max_chunk_size;
	float gain;
	double d_gain;


	Assert(Multi_voice_can_record);


	rtvoice_get_data((unsigned char**)&Multi_voice_record_buffer, &sound_size, &d_gain);
	gain = (float)d_gain;

	msg_mode = (ubyte)Multi_voice_send_mode;

	target_index = -1;
	if(msg_mode == MULTI_MSG_TARGET){
		if(Player_ai->target_objnum != -1){
			target_index = multi_find_player_by_object(&Objects[Player_ai->target_objnum]);
			if(target_index == -1){
				return;
			}
		} else {
			return;
		}
	}


	max_chunk_size = multi_voice_max_chunk_size(Multi_voice_send_mode);


	code = MV_CODE_DATA;
	chunk_index = 0;
	size_sent = 0;
	rbuf = (unsigned char*)Multi_voice_record_buffer;
	while(size_sent < sound_size){

		BUILD_HEADER(VOICE_PACKET);


		ADD_DATA(code);


		ADD_DATA(msg_mode);
		if(msg_mode == MULTI_MSG_TARGET){
			ADD_DATA(Objects[Net_players[target_index].m_player->objnum].net_signature);
		}


		ADD_SHORT(Net_player->player_id);


		ADD_DATA(Multi_voice_stream_id);

		Assert(sound_size < MULTI_VOICE_MAX_BUFFER_SIZE);
		uc_size = (ushort)sound_size;
		ADD_USHORT(uc_size);


		ADD_DATA(chunk_index);


		if((sound_size - size_sent) >= max_chunk_size){
			chunk_size = (ushort)max_chunk_size;
		} else {
			chunk_size = (ushort)(sound_size - size_sent);
		}
		ADD_USHORT(chunk_size);


		ADD_FLOAT(gain);


		memcpy(data+packet_size, rbuf,chunk_size);
		packet_size += chunk_size;


		if(Net_player->flags & NETINFO_FLAG_AM_MASTER){
			multi_voice_route_data(data,packet_size,MY_NET_PLAYER_NUM,(int)msg_mode,(target_index == -1) ? NULL : &Net_players[target_index]);
		} else {
			multi_io_send(Net_player, data, packet_size);
		}


		chunk_index++;


		size_sent += (int)chunk_size;
		rbuf += chunk_size;
	}
}
