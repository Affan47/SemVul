send_endgame_packet(net_player *pl)
{
	ubyte data[MAX_PACKET_SIZE];
	int packet_size;

	packet_size = 0;
	BUILD_HEADER(MISSION_END);


	if(pl != NULL){
		Assert(Net_player->flags & NETINFO_FLAG_AM_MASTER);
		multi_io_send_reliable(pl, data, packet_size);
		return;
	}

	if(Net_player->flags & NETINFO_FLAG_AM_MASTER){

		multi_broadcast_stats(STATS_MISSION);


		ml_string("Before dogfight stats!");
		if(Netgame.type_flags & NG_TYPE_DOGFIGHT){
			ml_string("Sending dogfight stats!");

			multi_broadcast_stats(STATS_DOGFIGHT_KILLS);
		}
		ml_string("After dogfight stats!");


		multi_io_send_to_all_reliable(data, packet_size);
	} else {
		multi_io_send_reliable(Net_player, data, packet_size);
	}
}
