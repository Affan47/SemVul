multi_create_sw_clicked()
{
	netgame_info ng_temp;
	netgame_info *ng;
	multi_create_info *mcip;

	int file_index = multi_create_select_to_index(Multi_create_list_select);

	if (file_index < 0) {
		Int3();

		if ( Multi_create_sw_checkbox.checked() ) {
			Multi_create_sw_checkbox.set_state(0);
		}

		return;
	}

	if (Multi_create_list_mode == MULTI_CREATE_SHOW_MISSIONS) {
		mcip = &Multi_create_mission_list[file_index];
	} else {
		mcip = &Multi_create_campaign_list[file_index];
	}


	if(MULTIPLAYER_MASTER){
		ng = &Netgame;
	} else {
		ng_temp = Netgame;
		ng = &ng_temp;
	}


	if(!Multi_create_sw_checkbox.checked()){


		if (mcip->flags & MISSION_TYPE_MULTI_TEAMS) {
			ng->type_flags = NG_TYPE_TVT;
		} else if (mcip->flags & MISSION_TYPE_MULTI_DOGFIGHT) {
			ng->type_flags = NG_TYPE_DOGFIGHT;
		} else {
			ng->type_flags = NG_TYPE_COOP;
		}
	}

	else {

		ng->type_flags = NG_TYPE_SW;
	}


	if(Net_player->flags & NETINFO_FLAG_AM_MASTER){

		send_netgame_update_packet();


		multi_options_update_netgame();
	}

	else {

		multi_options_update_mission(ng, Multi_create_list_mode == MULTI_CREATE_SHOW_CAMPAIGNS ? 1 : 0);
	}
}
