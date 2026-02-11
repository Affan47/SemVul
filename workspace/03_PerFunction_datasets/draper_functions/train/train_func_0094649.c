ipvs_group_remove_entry(virtual_server_t *vs, virtual_server_group_entry_t *vsge)
{
	real_server_t *rs;
	element e;
	list l = vs->rs;


	memset(srule, 0, sizeof(ipvs_service_t));
	memset(drule, 0, sizeof(ipvs_dest_t));


	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		rs = ELEMENT_DATA(e);

		if (rs->alive) {

			if (!drule->addr.ip) {

				ipvs_set_rule(IP_VS_SO_SET_DELDEST, vs, rs);
			} else {
				drule->af = rs->addr.ss_family;
				if (rs->addr.ss_family == AF_INET6)
					inet_sockaddrip6(&rs->addr, &drule->addr.in6);
				else
					drule->addr.ip = inet_sockaddrip4(&rs->addr);
				drule->port = inet_sockaddrport(&rs->addr);
				drule->weight = rs->weight;
			}


			if (vsge->range) {
				ipvs_group_range_cmd(IP_VS_SO_SET_DELDEST, vsge);
			} else {
				srule->af = vsge->addr.ss_family;
				if (vsge->addr.ss_family == AF_INET6)
					inet_sockaddrip6(&vsge->addr, &srule->addr.in6);
				else
					srule->addr.ip = inet_sockaddrip4(&vsge->addr);
				srule->port = inet_sockaddrport(&vsge->addr);
				srule->fwmark = vsge->vfwmark;
				drule->u_threshold = rs->u_threshold;
				drule->l_threshold = rs->l_threshold;


				ipvs_talk(IP_VS_SO_SET_DELDEST);
			}
		}
	}


	if (vsge->range)
		ipvs_group_range_cmd(IP_VS_SO_SET_DEL, vsge);
	else
		ipvs_talk(IP_VS_SO_SET_DEL);

	return IPVS_SUCCESS;
}
