send_leave_game_packet(short player_id, int kicked_reason, net_player *target)
{
	ubyte data[MAX_PACKET_SIZE];
	char val;
	int packet_size = 0;

	BUILD_HEADER(LEAVE_GAME);


	val = (char)kicked_reason;
	ADD_DATA(val);

	if (player_id < 0) {
		ADD_SHORT(Net_player->player_id);


		if (Net_player->flags & NETINFO_FLAG_AM_MASTER) {
			multi_io_send_to_all_reliable(data, packet_size);
		} else {
			multi_io_send_reliable(Net_player, data, packet_size);
		}
	}


	else {
		nprintf(("Network","Sending a leave game packet to all players (server)\n"));


		Assert(player_id != Net_player->player_id);
		Assert(Net_player->flags & NETINFO_FLAG_AM_MASTER);


		ADD_SHORT(player_id);


		if (target == NULL) {
			multi_io_send_to_all_reliable(data, packet_size);
		} else {
			multi_io_send_reliable(target, data, packet_size);
		}
	}
}
