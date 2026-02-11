fs2netd_handle_ping()
{
	static int CONN_check = -1;


	if ( (Ping_timestamp != -1) && ((timer_get_seconds() - Ping_timestamp) > 30) ) {
		Ping_timestamp = -1;

		ml_string("FS2NetD WARNING: Lost connection to server!");
		fs2netd_reset_connection();


		if ( !Is_connected ) {
			if (!Is_standalone) {
				gamesnd_play_iface(SND_GENERAL_FAIL);
				popup(PF_USE_AFFIRMATIVE_ICON | PF_TITLE_BIG | PF_TITLE_RED, 1, POPUP_OK, "ERROR:\nLost connection to the FS2NetD server!");
			}

			ml_string("FS2NetD ERROR: Lost connection to the FS2NetD server!");

			fs2netd_disconnect();

			ml_string("FS2NetD MSG: Will attempt an automatic reconnect to server in 5 minutes...");
			Login_retry_time = timer_get_seconds() + 300;

			return;
		} else {
			ml_string("FS2NetD NOTICE: Connection to server has been reestablished!");
		}
	}


	if ( (Ping_timestamp == -1) && (timer_get_seconds() >= (Last_activity + 300)) ) {
		Ping_timestamp = timer_get_seconds();
		FS2NetD_Ping();
		ml_string("FS2NetD sent PING");

		if (Last_activity < 0) {
			Last_activity = timer_get_seconds();
		}
	}


	if ( (CONN_check == -1) || (timer_get_seconds() >= CONN_check) ) {

		CONN_check = timer_get_seconds() + 180;


		if ( FS2NetD_CheckValidID() < 0 ) {
			ml_string("FS2NetD WARNING: Unable to validate login!");
			fs2netd_reset_connection();


			if ( !Is_connected ) {
				if (!Is_standalone) {
					gamesnd_play_iface(SND_GENERAL_FAIL);
					popup(PF_USE_AFFIRMATIVE_ICON | PF_TITLE_BIG | PF_TITLE_RED, 1, POPUP_OK, "ERROR:\nLost connection to the FS2NetD server!");
				}

				ml_string("FS2NetD ERROR: Lost connection to the FS2NetD server!");

				fs2netd_disconnect();

				ml_string("FS2NetD MSG: Will attempt an automatic reconnect to server in 5 minutes...");
				Login_retry_time = timer_get_seconds() + 300;

				return;
			} else {
				ml_string("FS2NetD NOTICE: Connection to server has been reestablished!");
			}
		}


		if ( (Netgame.game_state == NETGAME_STATE_BRIEFING) || (Netgame.game_state == NETGAME_STATE_MISSION_SYNC) ) {
			FS2NetD_CheckDuplicateLogin();
		}

		ml_string("FS2NetD sent IDENT check");
	}
}
