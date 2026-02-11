multi_file_xfer_notify(int handle)
{
	char *filename;
	int len,idx;
	int force_dir;
	int cf_type;
	int is_mission = 0;


	filename = NULL;
	filename = multi_xfer_get_filename(handle);


	force_dir = multi_xfer_get_force_dir(handle);


	if(filename == NULL){
		return;
	}


	len = strlen(filename);
	for(idx=0;idx<len;idx++){
		filename[idx] = (char)tolower(filename[idx]);
	}


	is_mission = (strstr(filename, FS_MISSION_FILE_EXT) != NULL);


	if(is_mission){
		cf_type = Net_player->p_info.options.flags & MLO_FLAG_XFER_MULTIDATA ? CF_TYPE_MULTI_CACHE : CF_TYPE_MISSIONS;
	} else {
		cf_type = CF_TYPE_MULTI_CACHE;
	}


	if((filename[0] != '\0') && !cf_access(filename, cf_type, 00) && (cf_access(filename, cf_type, 02) == -1)){
		multi_xfer_xor_flags(handle, MULTI_XFER_FLAG_REJECT);

		Net_player->flags &= ~(NETINFO_FLAG_DO_NETWORKING);
		popup(PF_USE_AFFIRMATIVE_ICON, 1, XSTR("&Ok", 713), XSTR("An outdated copy of this file exists, but it cannot be overwritten by the server because it is set to be read-only. Change the permissions on this file next time.", 714));
		multi_quit_game(PROMPT_NONE);
		return;
	}


	if(is_mission){

		Assert(Net_player->s_info.xfer_handle == -1);


		multi_xfer_handle_force_dir(handle, cf_type);


		Net_player->s_info.xfer_handle = handle;

		Net_player->state = NETPLAYER_STATE_MISSION_XFER;
		send_netplayer_update_packet();
	}

	else {
		multi_data_handle_incoming(handle);
	}
}
