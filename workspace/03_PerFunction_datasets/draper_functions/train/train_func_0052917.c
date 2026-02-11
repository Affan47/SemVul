send_netgame_descript_packet(net_addr *addr, int code)
{
	ubyte data[MAX_PACKET_SIZE],val;
	int desc_len;
	int packet_size = 0;


	BUILD_HEADER(UPDATE_DESCRIPT);

	val = (ubyte)code;
	ADD_DATA(val);

	if(code == 1){

		desc_len = strlen(The_mission.mission_desc);
		if(desc_len > MAX_PACKET_SIZE - 10){
			desc_len = MAX_PACKET_SIZE - 10;
			ADD_INT(desc_len);
			memcpy(data+packet_size, The_mission.mission_desc, desc_len);
			packet_size += desc_len;
		} else {
			ADD_STRING(The_mission.mission_desc);
		}
	}

	Assert(addr != NULL);
	if(addr != NULL){
		psnet_send(addr, data, packet_size);
	}
}
