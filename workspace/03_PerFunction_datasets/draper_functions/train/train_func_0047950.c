iscsi_host_set_net_params(struct iface_rec *iface,
			      struct iscsi_session *session)
{
	struct iscsi_transport *t = session->t;
	int rc = 0;
	char *netdev;
	struct host_info hinfo;

	log_debug(3, "setting iface %s, dev %s, set ip %s, hw %s, "
		  "transport %s.",
		  iface->name, iface->netdev, iface->ipaddress,
		  iface->hwaddress, iface->transport_name);

	if (!t->template->set_host_ip)
		return 0;


	if (!iface_is_bound_by_ipaddr(iface)) {
		if (t->template->set_host_ip == SET_HOST_IP_REQ) {
			log_warning("Please set the iface.ipaddress for iface "
				    "%s, then retry the login command.",
				    iface->name);
			return EINVAL;
		} else if (t->template->set_host_ip == SET_HOST_IP_OPT) {
			log_info("Optional iface.ipaddress for iface %s "
				 "not set.", iface->name);
			return 0;
		} else {
			return EINVAL;
		}
	}


	if (strlen(iface->netdev))
		netdev = iface->netdev;
	else {
		memset(&hinfo, 0, sizeof(hinfo));
		hinfo.host_no = session->hostno;
		iscsi_sysfs_get_hostinfo_by_host_no(&hinfo);

		netdev = hinfo.iface.netdev;
	}

	if (net_ifup_netdev(netdev))
		log_warning("Could not brining up netdev %s. Try running "
			    "'ifup %s' first if login fails.", netdev, netdev);

	rc = iscsi_set_net_config(t, session, iface);
	if (rc != 0)
		return rc;

	rc = host_set_param(t, session->hostno,
			    ISCSI_HOST_PARAM_IPADDRESS,
			    iface->ipaddress, ISCSI_STRING);
	if (rc)
		return rc;

	if (iface_is_bound_by_netdev(iface)) {
		rc = host_set_param(t, session->hostno,
				    ISCSI_HOST_PARAM_NETDEV_NAME,
				    iface->netdev, ISCSI_STRING);
		if (rc)
			return rc;
	}

	if (iface_is_bound_by_hwaddr(iface)) {
		rc = host_set_param(t, session->hostno,
				    ISCSI_HOST_PARAM_HWADDRESS,
				    iface->hwaddress, ISCSI_STRING);
		if (rc)
			return rc;
	}
	return 0;
}
