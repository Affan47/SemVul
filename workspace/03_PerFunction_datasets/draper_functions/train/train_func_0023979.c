pause_proxies(void)
{
	int err;
	struct proxy *p;

	err = 0;
	p = proxy;
	tv_update_date(0,1);
	while (p) {
		if (p->cap & PR_CAP_FE &&
		    p->state != PR_STERROR &&
		    p->state != PR_STSTOPPED &&
		    p->state != PR_STPAUSED) {
			Warning("Pausing %s %s.\n", proxy_cap_str(p->cap), p->id);
			send_log(p, LOG_WARNING, "Pausing %s %s.\n", proxy_cap_str(p->cap), p->id);
			pause_proxy(p);
			if (p->state != PR_STPAUSED) {
				err |= 1;
				Warning("%s %s failed to enter pause mode.\n", proxy_cap_str(p->cap), p->id);
				send_log(p, LOG_WARNING, "%s %s failed to enter pause mode.\n", proxy_cap_str(p->cap), p->id);
			}
		}
		p = p->next;
	}
	if (err) {
		Warning("Some proxies refused to pause, performing soft stop now.\n");
		send_log(p, LOG_WARNING, "Some proxies refused to pause, performing soft stop now.\n");
		soft_stop();
	}
}
