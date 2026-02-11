multi_pause_request(int pause)
{

	if(Net_player->flags & NETINFO_FLAG_AM_MASTER){
		multi_pause_server_eval_request(Net_player,pause);
	}

	else {
		send_multi_pause_packet(pause);
	}
}
