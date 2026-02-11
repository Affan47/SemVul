send_countdown_packet(int time)
{
	ubyte data[20];
	char val;
	int packet_size = 0;


	BUILD_HEADER(COUNTDOWN);
	val = (char)time;
	ADD_DATA(val);


	if(Net_player->flags & NETINFO_FLAG_AM_MASTER){
		multi_io_send_to_all_reliable(data, packet_size);
	}

	else {
		Assert(Net_player->flags & NETINFO_FLAG_GAME_HOST);
		multi_io_send_reliable(Net_player, data, packet_size);
	}
}
