run_free_trials(int bout) {
	int n, msg, side;
	time_t time_stamp;
	for (n = 0; time_check() && n < free_trials; n++) {
		flush_events();

		send_msg(RPiMsgSetOn | RPiPin(4) | RPiPin(5));

		for (;;) {
			if (!time_check()) return 1;
			if ( (msg=check_event(1,0)) &&
				(msg & RPiEventChange) &&
				(msg & (RPiPin(0)|RPiPin(1))) ) break;
		}
		side = ((msg & RPiPinMask) == RPiPin(0) ? 0 : 1);

		time_stamp = time(NULL);
		send_msg(RPiMsgSetOff | RPiPin(4) | RPiPin(5));
		log_data(bout, n, time_stamp - start_time, side);
		play_song(side);
		while (time_check() && now < time_stamp + intertrial_sec) {
			flush_events();
			sleep(1);
		}
	}
	return 0;
}
