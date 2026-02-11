init_if_linkbeat(void)
{
	interface *ifp;
	element e;
	int status;

	for (e = LIST_HEAD(if_queue); e; ELEMENT_NEXT(e)) {
		ifp = ELEMENT_DATA(e);
		ifp->lb_type = LB_IOCTL;
		status = if_mii_probe(ifp->ifname);
		if (status >= 0) {
			ifp->lb_type = LB_MII;
			ifp->linkbeat = (status) ? 1 : 0;
		} else {
			status = if_ethtool_probe(ifp->ifname);
			if (status >= 0) {
				ifp->lb_type = LB_ETHTOOL;
				ifp->linkbeat = (status) ? 1 : 0;
			}
		}


		thread_add_timer(master, if_linkbeat_refresh_thread, ifp, POLLING_DELAY);
	}
}
