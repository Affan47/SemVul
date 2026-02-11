verify_iface_params(struct list_head *params, struct node_rec *rec)
{
	struct user_param *param;

	list_for_each_entry(param, params, list) {
		if (!strcmp(param->name, IFACE_ISCSINAME)) {
			log_error("Can not update "
				  "iface.iscsi_ifacename. Delete it, "
				  "and then create a new one.");
			return ISCSI_ERR_INVAL;
		}

		if (iface_is_bound_by_hwaddr(&rec->iface) &&
		    !strcmp(param->name, IFACE_NETNAME)) {
			log_error("Can not update interface binding "
				  "from hwaddress to net_ifacename. "
				  "You must delete the interface and "
				  "create a new one");
			return ISCSI_ERR_INVAL;
		}

		if (iface_is_bound_by_netdev(&rec->iface) &&
		    !strcmp(param->name, IFACE_HWADDR)) {
			log_error("Can not update interface binding "
				  "from net_ifacename to hwaddress. "
				  "You must delete the interface and "
				  "create a new one");
			return ISCSI_ERR_INVAL;
		}
	}
	return 0;
}
