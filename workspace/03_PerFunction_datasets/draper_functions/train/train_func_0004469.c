fs2netd_do_frame()
{

	if ( In_process ) {
		return;
	}

	if ( !Logged_in ) {

		if ( (Login_retry_time != -1) && (timer_get_seconds() >= Login_retry_time) ) {
			fs2netd_login();

			if ( !Logged_in ) {

				Login_retry_time = timer_get_seconds() + 300;
			} else {
				Login_retry_time = -1;
			}
		}

		return;
	}


	fs2netd_handle_ping();


	fs2netd_gameserver_update();


	fs2netd_handle_messages();


	if (Is_connected && !Logged_in) {
		fs2netd_login();
	}
}
