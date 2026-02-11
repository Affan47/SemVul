hud_squadmsg_toggle()
{

	if(emp_active_local()){
		return;
	}


	if ( !(Player->flags & PLAYER_FLAGS_MSG_MODE) ) {
		if ( Game_mode & GM_DEAD ){
			return;
		}

		if ( (Game_mode & GM_MULTIPLAYER) && NETPLAYER_IS_OBSERVER(Net_player) ){
			return;
		}

		hud_squadmsg_start();
	} else {
		hud_squadmsg_end();
	}

	Player->flags ^= PLAYER_FLAGS_MSG_MODE;
}
