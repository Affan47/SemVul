soft_stop(void)
{
	struct proxy *p;

	stopping = 1;
	p = proxy;
	tv_update_date(0,1);
	while (p) {
		if (p->state != PR_STSTOPPED) {
			Warning("Stopping %s %s in %d ms.\n", proxy_cap_str(p->cap), p->id, p->grace);
			send_log(p, LOG_WARNING, "Stopping %s %s in %d ms.\n", proxy_cap_str(p->cap), p->id, p->grace);
			p->stop_time = tick_add(now_ms, p->grace);
		}
		p = p->next;
	}
}
