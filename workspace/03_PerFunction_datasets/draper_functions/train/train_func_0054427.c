loop_for_connect(int did_client_connect) {
	int loop = 0;
	time_t start = time(NULL);

	if (first_conn_timeout < 0) {
		first_conn_timeout = -first_conn_timeout;
	}

	while (1) {
		loop++;
		if (first_conn_timeout && time(NULL) > start + first_conn_timeout) {
			rfbLog("no client connect after %d seconds.\n", first_conn_timeout);
			shut_down = 1;
		}
		if (shut_down) {
			clean_up_exit(0);
		}
		if (loop < 2) {
			if (did_client_connect) {
				goto screen_check;
			}
			if (inetd) {
				goto screen_check;
			}
			if (screen && screen->clientHead) {
				goto screen_check;
			}
		}
		if ((use_openssl || use_stunnel) && !inetd) {
			int enc_none = (enc_str && !strcmp(enc_str, "none"));
			if (!use_stunnel || enc_none) {
				check_openssl();
				check_https();
			}


			if (use_threads) {
				usleep(10 * 1000);
			} else {
				rfbPE(-1);
			}
			if (screen && screen->clientHead) {
				int i;
				if (unixpw) {
					if (! unixpw_in_progress && !vencrypt_enable_plain_login) {
						rfbLog("unixpw but no unixpw_in_progress\n");
						clean_up_exit(1);
					}
					if (unixpw_client && unixpw_client->onHold) {
						rfbLog("taking unixpw_client off hold\n");
						unixpw_client->onHold = FALSE;
					}
				}
				for (i=0; i<10; i++) {
					if (shut_down) {
						clean_up_exit(0);
					}
					usleep(20 * 1000);
					if (0) rfbLog("wait_for_client: %d\n", i);

					if (! use_threads) {
						if (unixpw) {
							unixpw_in_rfbPE = 1;
						}
						rfbPE(-1);
						if (unixpw) {
							unixpw_in_rfbPE = 0;
						}
					}

					if (unixpw && !unixpw_in_progress) {

						goto screen_check;
					}
					if (!screen->clientHead) {
						break;
					}
				}
			}
		} else if (use_openssl) {
			check_openssl();
		}

		if (use_threads) {
			usleep(10 * 1000);
		} else {
			rfbPE(-1);
		}

		screen_check:
		if (! screen || ! screen->clientHead) {
			usleep(100 * 1000);
			continue;
		}

		rfbLog("wait_for_client: got client\n");
		break;
	}
}
