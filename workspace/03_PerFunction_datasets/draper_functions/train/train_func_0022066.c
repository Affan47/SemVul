ipvs_set_rule(int cmd, virtual_server * vs, real_server * rs)
{

	memset(drule, 0, sizeof(ipvs_dest_t));

	drule->weight = 1;
	drule->u_threshold = 0;
	drule->l_threshold = 0;
	drule->conn_flags = vs->loadbalancing_kind;
	strncpy(srule->sched_name, vs->sched, IP_VS_SCHEDNAME_MAXLEN);
	srule->netmask = (vs->addr.ss_family == AF_INET6) ? 128 : ((u_int32_t) 0xffffffff);
	srule->protocol = vs->service_type;

	if (!parse_timeout(vs->timeout_persistence, &srule->timeout))
		log_message(LOG_INFO, "IPVS : Virtual service [%s]:%d illegal timeout."
				    , inet_ntop2(inet_sockaddrip4(&vs->addr))
				    , ntohs(inet_sockaddrport(&vs->addr)));

	if (srule->timeout != 0 || vs->granularity_persistence)
		srule->flags = IP_VS_SVC_F_PERSISTENT;

	if (cmd == IP_VS_SO_SET_ADD || cmd == IP_VS_SO_SET_DEL)
		if (vs->granularity_persistence)
			srule->netmask = vs->granularity_persistence;


	if (rs) {
		if (cmd == IP_VS_SO_SET_ADDDEST || cmd == IP_VS_SO_SET_DELDEST ||
		    cmd == IP_VS_SO_SET_EDITDEST) {
			drule->af = rs->addr.ss_family;
			if (rs->addr.ss_family == AF_INET6)
				inet_sockaddrip6(&rs->addr, &drule->addr.in6);
			else
				drule->addr.ip = inet_sockaddrip4(&rs->addr);
			drule->port = inet_sockaddrport(&rs->addr);
			drule->weight = rs->weight;
			drule->u_threshold = rs->u_threshold;
			drule->l_threshold = rs->l_threshold;
		}
	}
}
