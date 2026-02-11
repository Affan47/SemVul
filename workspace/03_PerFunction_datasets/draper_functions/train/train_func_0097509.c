dump_vs(void *data)
{
	virtual_server *vs = data;

	if (vs->vsgname)
		log_message(LOG_INFO, " VS GROUP = %s", vs->vsgname);
	else if (vs->vfwmark)
		log_message(LOG_INFO, " VS FWMARK = %d", vs->vfwmark);
	else
		log_message(LOG_INFO, " VIP = %s, VPORT = %d"
				    , inet_sockaddrtos(&vs->addr), ntohs(inet_sockaddrport(&vs->addr)));
	if (vs->virtualhost)
		log_message(LOG_INFO, "   VirtualHost = %s", vs->virtualhost);
	log_message(LOG_INFO, "   delay_loop = %lu, lb_algo = %s",
	       (vs->delay_loop >= TIMER_MAX_SEC) ? vs->delay_loop/TIMER_HZ :
						   vs->delay_loop,
	       vs->sched);
	if (atoi(vs->timeout_persistence) > 0)
		log_message(LOG_INFO, "   persistence timeout = %s",
		       vs->timeout_persistence);
	if (vs->granularity_persistence)
		log_message(LOG_INFO, "   persistence granularity = %s",
		       inet_ntop2(vs->granularity_persistence));
	log_message(LOG_INFO, "   protocol = %s",
	       (vs->service_type == IPPROTO_TCP) ? "TCP" : "UDP");
	log_message(LOG_INFO, "   alpha is %s, omega is %s",
		    vs->alpha ? "ON" : "OFF", vs->omega ? "ON" : "OFF");
	log_message(LOG_INFO, "   quorum = %lu, hysteresis = %lu", vs->quorum, vs->hysteresis);
	if (vs->quorum_up)
		log_message(LOG_INFO, "   -> Notify script UP = %s",
			    vs->quorum_up);
	if (vs->quorum_down)
		log_message(LOG_INFO, "   -> Notify script DOWN = %s",
			    vs->quorum_down);
	if (vs->ha_suspend)
		log_message(LOG_INFO, "   Using HA suspend");

	switch (vs->loadbalancing_kind) {
#ifdef _WITH_LVS_
	case IP_VS_CONN_F_MASQ:
		log_message(LOG_INFO, "   lb_kind = NAT");
		break;
	case IP_VS_CONN_F_DROUTE:
		log_message(LOG_INFO, "   lb_kind = DR");
		break;
	case IP_VS_CONN_F_TUNNEL:
		log_message(LOG_INFO, "   lb_kind = TUN");
		break;
#endif
	}

	if (vs->s_svr) {
		log_message(LOG_INFO, "   sorry server = [%s]:%d"
				    , inet_sockaddrtos(&vs->s_svr->addr)
				    , ntohs(inet_sockaddrport(&vs->s_svr->addr)));
	}
	if (!LIST_ISEMPTY(vs->rs))
		dump_list(vs->rs);
}
