fs2netd_options_config_init()
{
	if (PXO_options_loaded) {
		return;
	}

	if ( !strlen(Multi_options_g.game_tracker_ip) ) {
		ml_printf("NOTICE: Address for game tracker not specified, using default instead (%s).", FS2NETD_DEFAULT_SERVER);
		strncpy( Multi_options_g.game_tracker_ip, FS2NETD_DEFAULT_SERVER, MULTI_OPTIONS_STRING_LEN );
	} else if ( !strcmp("gt.pxo.net", Multi_options_g.game_tracker_ip) ) {
		ml_printf("NOTICE: Incompatible game tracker IP detected (gt.pxo.net), using default instead (%s)!", FS2NETD_DEFAULT_SERVER);
		strncpy( Multi_options_g.game_tracker_ip, FS2NETD_DEFAULT_SERVER, MULTI_OPTIONS_STRING_LEN );
	}

	if ( !strlen(Multi_options_g.user_tracker_ip) ) {
		ml_printf("NOTICE: Address for user tracker not specified, using default instead (%s).", FS2NETD_DEFAULT_SERVER);
		strncpy( Multi_options_g.user_tracker_ip, FS2NETD_DEFAULT_SERVER, MULTI_OPTIONS_STRING_LEN );
	} else if ( !strcmp("ut.pxo.net", Multi_options_g.user_tracker_ip) ) {
		ml_printf("NOTICE: Incompatible user tracker IP detected (ut.pxo.net), using default instead (%s)!", FS2NETD_DEFAULT_SERVER);
		strncpy( Multi_options_g.user_tracker_ip, FS2NETD_DEFAULT_SERVER, MULTI_OPTIONS_STRING_LEN );
	}

	if ( !strlen(Multi_options_g.tracker_port) ) {
		ml_printf("NOTICE: Port for game/user trackers not specified, using default instead (%s).", FS2NETD_DEFAULT_PORT);
		strncpy( Multi_options_g.tracker_port, FS2NETD_DEFAULT_PORT, STD_NAME_LEN );
	} else {
		long port_tmp = strtol(Multi_options_g.tracker_port, (char**)NULL, 10);

		if ( (port_tmp < 1024) || (port_tmp > USHRT_MAX) ) {
			ml_printf("NOTICE: The port specified for game/user trackers, '%i', is outside of the required range, %i through %i!", port_tmp, 1024, USHRT_MAX);
			ml_printf("NOTICE: Port for game/user trackers is invalid, using default instead (%s).", FS2NETD_DEFAULT_PORT);
			strncpy( Multi_options_g.tracker_port, FS2NETD_DEFAULT_PORT, STD_NAME_LEN );
		}
	}

	if ( !strlen(Multi_options_g.pxo_ip) ) {
		ml_printf("NOTICE: Address for chat server not specified, using default instead (%s).", FS2NETD_DEFAULT_CHAT_SERVER);
		strncpy( Multi_options_g.pxo_ip, FS2NETD_DEFAULT_CHAT_SERVER, MULTI_OPTIONS_STRING_LEN );
	} else if ( !strcmp("chat.pxo.net", Multi_options_g.pxo_ip) ) {
		ml_printf("NOTICE: Incompatible chat server IP detected (chat.pxo.net), using default instead (%s)!", FS2NETD_DEFAULT_CHAT_SERVER);
		strncpy( Multi_options_g.pxo_ip, FS2NETD_DEFAULT_CHAT_SERVER, MULTI_OPTIONS_STRING_LEN );
	}

	if ( !strlen(Multi_options_g.pxo_banner_url) ) {
		ml_printf("NOTICE: URL for banners not specified, using default instead (%s).", FS2NETD_DEFAULT_BANNER_URL);
		strncpy( Multi_options_g.pxo_banner_url, FS2NETD_DEFAULT_BANNER_URL, MULTI_OPTIONS_STRING_LEN );
	} else if ( !strcmp("http://www.pxo.net/files/banners", Multi_options_g.pxo_banner_url) ) {
		ml_printf("NOTICE: Incompatible banner URL detected (chat.pxo.net), using default instead (%s)!", FS2NETD_DEFAULT_BANNER_URL);
		strncpy( Multi_options_g.pxo_banner_url, FS2NETD_DEFAULT_BANNER_URL, MULTI_OPTIONS_STRING_LEN );
	}

	PXO_options_loaded = true;
}
