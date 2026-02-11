start_proxies(int verbose)
{
	struct proxy *curproxy;
	struct listener *listener;
	int lerr, err = ERR_NONE;
	int pxerr;
	char msg[100];

	for (curproxy = proxy; curproxy != NULL; curproxy = curproxy->next) {
		if (curproxy->state != PR_STNEW)
			continue;

		pxerr = 0;
		list_for_each_entry(listener, &curproxy->conf.listeners, by_fe) {
			if (listener->state != LI_ASSIGNED)
				continue;

			lerr = listener->proto->bind(listener, msg, sizeof(msg));


			if (verbose || (lerr & (ERR_FATAL | ERR_ABORT))) {
				if (lerr & ERR_ALERT)
					Alert("Starting %s %s: %s\n",
					      proxy_type_str(curproxy), curproxy->id, msg);
				else if (lerr & ERR_WARN)
					Warning("Starting %s %s: %s\n",
						proxy_type_str(curproxy), curproxy->id, msg);
			}

			err |= lerr;
			if (lerr & (ERR_ABORT | ERR_FATAL)) {
				pxerr |= 1;
				break;
			}
			else if (lerr & ERR_CODE) {
				pxerr |= 1;
				continue;
			}
		}

		if (!pxerr) {
			curproxy->state = PR_STREADY;
			send_log(curproxy, LOG_NOTICE, "Proxy %s started.\n", curproxy->id);
		}

		if (err & ERR_ABORT)
			break;
	}

	return err;
}
