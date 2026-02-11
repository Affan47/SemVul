rfbPE(long usec) {
	int uip0 = unixpw_in_progress;
	static int check_rate = -1;
	int res = 0;
	if (! screen) {
		return res;
	}
 	if (unixpw && unixpw_in_progress && !unixpw_in_rfbPE) {
		rfbLog("unixpw_in_rfbPE: skipping rfbPE\n");
 		return res;
 	}

	if (debug_tiles > 2) {
		double tm = dnow();
		fprintf(stderr, "rfbPE(%d)  t: %.4f\n",
		    (int) usec, tm - x11vnc_start);
	}

	if (usec > USEC_MAX) {
		usec = USEC_MAX;
	}
	if (! use_threads) {
		rfbBool r;
		r = rfbProcessEvents(screen, usec);
		if (r) {
			res = 1;
		}
	}

 	if (unixpw && unixpw_in_progress && !uip0) {
		if (!unixpw_in_rfbPE) {
			rfbLog("rfbPE: got new client in non-rfbPE\n");
			;
		}
 	}

	if (ipv6_listen) {
		check_ipv6_listen(usec);
	}
	if (unix_sock) {
		check_unix_sock(usec);
	}
	if (check_rate != 0) {
		if (check_rate < 0) {
			if (getenv("CHECK_RATE")) {
				check_rate = 1;
			} else {
				check_rate = 0;
			}
		}
		if (check_rate && !all_input && x11vnc_current < last_client + 45)  {
			check_allinput_rate();
		}
	}
	if (all_input) {
		do_allinput(usec);
	}
	return res;
}
