resume_proxy(struct proxy *p)
{
	struct listener *l;
	int fail;

	if (p->state != PR_STPAUSED)
		return 1;

	Warning("Enabling %s %s.\n", proxy_cap_str(p->cap), p->id);
	send_log(p, LOG_WARNING, "Enabling %s %s.\n", proxy_cap_str(p->cap), p->id);

	fail = 0;
	list_for_each_entry(l, &p->conf.listeners, by_fe) {
		if (!resume_listener(l)) {
			int port;

			port = get_host_port(&l->addr);
			if (port) {
				Warning("Port %d busy while trying to enable %s %s.\n",
					port, proxy_cap_str(p->cap), p->id);
				send_log(p, LOG_WARNING, "Port %d busy while trying to enable %s %s.\n",
					 port, proxy_cap_str(p->cap), p->id);
			}
			else {
				Warning("Bind on socket %d busy while trying to enable %s %s.\n",
					l->luid, proxy_cap_str(p->cap), p->id);
				send_log(p, LOG_WARNING, "Bind on socket %d busy while trying to enable %s %s.\n",
					 l->luid, proxy_cap_str(p->cap), p->id);
			}


			fail = 1;
			break;
		}
	}

	p->state = PR_STREADY;
	if (fail) {
		pause_proxy(p);
		return 0;
	}
	return 1;
}
