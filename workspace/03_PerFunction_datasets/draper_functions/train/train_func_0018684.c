send_wss_request_packet(short player_id, int from_slot, int from_index, int to_slot, int to_index, int wl_ship_slot, int ship_class, int mode, net_player *p)
{
	ubyte data[MAX_PACKET_SIZE];

	int packet_size = 0;

	BUILD_HEADER(WSS_REQUEST_PACKET);


	ADD_SHORT(player_id);
	ADD_INT(from_slot);
	ADD_INT(from_index);
	ADD_INT(to_slot);
	ADD_INT(to_index);
	ADD_INT(wl_ship_slot);
	ADD_INT(ship_class);
	ADD_INT(mode);


	if(p == NULL){
		multi_io_send_reliable(Net_player, data, packet_size);
	}

	else {
		Assert(Game_mode & GM_STANDALONE_SERVER);
		multi_io_send_reliable(p, data, packet_size);
	}
}
