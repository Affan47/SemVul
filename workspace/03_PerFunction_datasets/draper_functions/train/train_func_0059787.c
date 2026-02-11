ip_change_handler(struct sigchld_handler_t *h, int status)
{
	struct pppd_compat_pd *pd = container_of(h, typeof(*pd), ip_change_hnd);
	if (conf_verbose) {
		log_switch(NULL, pd->ses);
		log_ppp_info2("pppd_compat: ip-change finished (%i)\n", status);
	}
	sched_yield();
	pd->res = status;
	triton_context_wakeup(pd->ses->ctrl->ctx);
}
