multi_debrief_replay_hit()
{

	Assert(Net_player->flags & NETINFO_FLAG_GAME_HOST);


	if(Multi_debrief_accept_hit){
		return;
	}


	Multi_debrief_accept_hit = 1;


	Net_player->state = NETPLAYER_STATE_DEBRIEF_REPLAY;
	send_netplayer_update_packet();
}
