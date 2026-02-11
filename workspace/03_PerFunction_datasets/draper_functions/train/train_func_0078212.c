message_filter_multi(int id)
{

	if(!(Game_mode & GM_MULTIPLAYER)){
		return 0;
	}


	if((id < 0) || (id >= Num_messages)){
		mprintf(("Filtering bogus mission message!\n"));
		return 1;
	}


	if(id < Num_builtin_messages){
	}

	else {

		if(Messages[id].multi_team < 0){
			return 0;
		}


		if(!(Netgame.type_flags & NG_TYPE_TEAM)){
			return 0;
		}


		if((Net_player != NULL) && (Net_player->p_info.team != Messages[id].multi_team)){
			mprintf(("Filtering team-based mission message!\n"));
			return 1;
		}
	}

	return 0;
}
