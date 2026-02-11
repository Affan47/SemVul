maintain_proxies(int *next)
{
	struct proxy *p;
	struct listener *l;
	unsigned int wait;

	p = proxy;


	if (actconn < global.maxconn) {
		for (; p; p = p->next) {

			if (p->feconn >= p->maxconn)
				goto do_block;

			if (p->fe_sps_lim &&
			    (wait = next_event_delay(&p->fe_sess_per_sec, p->fe_sps_lim, 1))) {


				*next = tick_first(*next, tick_add(now_ms, wait));
				goto do_block;
			}


			if (p->state == PR_STIDLE) {
				for (l = p->listen; l != NULL; l = l->next)
					enable_listener(l);
				p->state = PR_STRUN;
			}
			continue;

		do_block:
			if (p->state == PR_STRUN) {
				for (l = p->listen; l != NULL; l = l->next)
					disable_listener(l);
				p->state = PR_STIDLE;
			}
		}
	}
	else {
		while (p) {
			if (p->state == PR_STRUN) {
				for (l = p->listen; l != NULL; l = l->next)
					disable_listener(l);
				p->state = PR_STIDLE;
			}
			p = p->next;
		}
	}

	if (stopping) {
		p = proxy;
		while (p) {
			if (p->state != PR_STSTOPPED) {
				int t;
				t = tick_remain(now_ms, p->stop_time);
				if (t == 0) {
					Warning("Proxy %s stopped (FE: %lld conns, BE: %lld conns).\n",
						p->id, p->counters.cum_feconn, p->counters.cum_beconn);
					send_log(p, LOG_WARNING, "Proxy %s stopped (FE: %lld conns, BE: %lld conns).\n",
						 p->id, p->counters.cum_feconn, p->counters.cum_beconn);
					stop_proxy(p);

					pool_gc2();
				}
				else {
					*next = tick_first(*next, p->stop_time);
				}
			}
			p = p->next;
		}
	}
	return;
}
