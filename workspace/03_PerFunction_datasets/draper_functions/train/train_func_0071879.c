ctldev_open(void)
{
	log_debug(7, "in %s", __FUNCTION__);

	nlm_sendbuf = calloc(1, NLM_BUF_DEFAULT_MAX);
	if (!nlm_sendbuf) {
		log_error("can not allocate nlm_sendbuf");
		return -1;
	}

	nlm_recvbuf = calloc(1, NLM_BUF_DEFAULT_MAX);
	if (!nlm_recvbuf) {
		log_error("can not allocate nlm_recvbuf");
		goto free_nlm_sendbuf;
	}

	pdu_sendbuf = calloc(1, PDU_SENDBUF_DEFAULT_MAX);
	if (!pdu_sendbuf) {
		log_error("can not allocate nlm_sendbuf");
		goto free_nlm_recvbuf;
	}

	setparam_buf = calloc(1, NLM_SETPARAM_DEFAULT_MAX);
	if (!setparam_buf) {
		log_error("can not allocate setparam_buf");
		goto free_pdu_sendbuf;
	}

	ctrl_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_ISCSI);
	if (ctrl_fd < 0) {
		log_error("can not create NETLINK_ISCSI socket");
		goto free_setparam_buf;
	}

	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid();
	src_addr.nl_groups = 1;
	if (bind(ctrl_fd, (struct sockaddr *)&src_addr, sizeof(src_addr))) {
		log_error("can not bind NETLINK_ISCSI socket");
		goto close_socket;
	}

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0;
	dest_addr.nl_groups = 0;

	log_debug(7, "created NETLINK_ISCSI socket...");

	return ctrl_fd;

close_socket:
	close(ctrl_fd);
free_setparam_buf:
	free(setparam_buf);
free_pdu_sendbuf:
	free(pdu_sendbuf);
free_nlm_recvbuf:
	free(nlm_recvbuf);
free_nlm_sendbuf:
	free(nlm_sendbuf);
	return -1;
}
