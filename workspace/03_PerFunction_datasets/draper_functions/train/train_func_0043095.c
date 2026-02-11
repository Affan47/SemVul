levent_iface_recv(evutil_socket_t fd, short what, void *arg)
{
	struct lldpd *cfg = arg;
	char buffer[EVENT_BUFFER];
	int n;


	while (1) {
		n = read(fd, buffer, sizeof(buffer));
		if (n == -1 &&
		    (errno == EWOULDBLOCK ||
			errno == EAGAIN)) break;
		if (n == -1) {
			log_warn("event",
			    "unable to receive interface change notification message");
			return;
		}
		if (n == 0) {
			log_warnx("event",
			    "end of file reached while getting interface change notification message");
			return;
		}
	}


	struct timeval one_sec = {1, 0};
	TRACE(LLDPD_INTERFACES_NOTIFICATION());
	log_debug("event",
	    "received notification change, schedule an update of all interfaces in one second");
	if (cfg->g_iface_timer_event == NULL) {
		if ((cfg->g_iface_timer_event = evtimer_new(cfg->g_base,
			    levent_iface_trigger, cfg)) == NULL) {
			log_warnx("event",
			    "unable to create a new event to trigger interface update");
			return;
		}
	}
	if (evtimer_add(cfg->g_iface_timer_event, &one_sec) == -1) {
		log_warnx("event",
		    "unable to schedule interface updates");
		return;
	}
}
