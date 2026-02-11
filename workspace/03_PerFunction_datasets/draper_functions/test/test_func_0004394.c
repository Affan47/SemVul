multi_standalone_postgame_do()
{

	if((Netgame.game_state != NETGAME_STATE_DEBRIEF) && multi_netplayer_state_check(NETPLAYER_STATE_DEBRIEF, 1)){
		Netgame.game_state = NETGAME_STATE_DEBRIEF;
		send_netgame_update_packet();
		debrief_multi_server_stuff();
	}


	if(Netgame.game_state == NETGAME_STATE_DEBRIEF){
		multi_debrief_server_process();
	}
}
