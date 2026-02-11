ipvs_group_cmd(int cmd, list vs_group, real_server_t * rs, virtual_server_t * vs)
{
	virtual_server_group_t *vsg = ipvs_get_group_by_name(vs->vsgname, vs_group);
	virtual_server_group_entry_t *vsg_entry;
	list l;
	element e;


	if (!vsg) return;


	l = vsg->addr_ip;
	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		vsg_entry = ELEMENT_DATA(e);
		srule->af = vsg_entry->addr.ss_family;
		if (vsg_entry->addr.ss_family == AF_INET6) {
			if (srule->netmask == 0xffffffff)
				srule->netmask = 128;
			inet_sockaddrip6(&vsg_entry->addr, &srule->addr.in6);
		} else
			srule->addr.ip = inet_sockaddrip4(&vsg_entry->addr);
		srule->port = inet_sockaddrport(&vsg_entry->addr);


		if (IPVS_ALIVE(cmd, vsg_entry, rs)) {
			ipvs_talk(cmd);
			IPVS_SET_ALIVE(cmd, vsg_entry);
		}
	}


	l = vsg->vfwmark;
	srule->addr.ip = 0;
	srule->af = 0;
	srule->port = 0;
	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		vsg_entry = ELEMENT_DATA(e);
		srule->af = AF_INET;

		if (vs->rs && !LIST_ISEMPTY(vs->rs) &&
		    (((real_server_t *)ELEMENT_DATA(LIST_HEAD(vs->rs)))->addr.ss_family == AF_INET6)) {
			srule->af = AF_INET6;
			srule->netmask = 128;
		}
		srule->fwmark = vsg_entry->vfwmark;


		if (IPVS_ALIVE(cmd, vsg_entry, rs)) {
			ipvs_talk(cmd);
			IPVS_SET_ALIVE(cmd, vsg_entry);
		}
	}


	l = vsg->range;
	srule->fwmark = 0;
	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		vsg_entry = ELEMENT_DATA(e);


		if (IPVS_ALIVE(cmd, vsg_entry, rs)) {
			ipvs_group_range_cmd(cmd, vsg_entry);
			IPVS_SET_ALIVE(cmd, vsg_entry);
		}
	}
}
