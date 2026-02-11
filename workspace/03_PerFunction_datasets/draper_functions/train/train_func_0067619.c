iface_apply_net_config(struct iface_rec *iface, int op)
{
	int rc = ISCSI_ERR;
	uint32_t host_no;
	int param_count;
	int param_used;
	int iface_all = 0;
	int i;
	struct iovec *iovs = NULL;
	struct iovec *iov = NULL;
	struct iscsi_transport *t = NULL;
	int fd;

	log_debug(8, "Calling iscsid, to apply net config for"
		  "iface.name = %s", iface->name);

	if (op == OP_APPLY_ALL)
		iface_all = 1;

	param_count = iface_get_param_count(iface, iface_all);
	if (!param_count) {
		log_error("Nothing to configure.");
		return ISCSI_SUCCESS;
	}


	param_count += 2;
	iovs = calloc((param_count * sizeof(struct iovec)),
		       sizeof(char));
	if (!iovs) {
		log_error("Out of Memory.");
		return ISCSI_ERR_NOMEM;
	}


	param_used = iface_build_net_config(iface, iface_all, iovs);
	if (!param_used) {
		log_error("Build netconfig failed.");
		goto free_buf;
	}

	t = iscsi_sysfs_get_transport_by_name(iface->transport_name);
	if (!t) {
		log_error("Can't find transport.");
		goto free_buf;
	}

	host_no = iscsi_sysfs_get_host_no_from_hwinfo(iface, &rc);
	if (host_no == -1) {
		log_error("Can't find host_no.");
		goto free_buf;
	}
	rc = ISCSI_ERR;

	fd = ipc->ctldev_open();
	if (fd < 0) {
		log_error("Netlink open failed.");
		goto free_buf;
	}

	rc = ipc->set_net_config(t->handle, host_no, iovs, param_count);
	if (rc < 0)
		log_error("Set net_config failed. errno=%d", errno);

	ipc->ctldev_close();

free_buf:

	iov = iovs + 2;
	for (i = 0; i < param_used; i++, iov++) {
		if (iov->iov_base)
			free(iov->iov_base);
	}

	free(iovs);
	if (rc)
		return ISCSI_ERR;
	return ISCSI_SUCCESS;
}
