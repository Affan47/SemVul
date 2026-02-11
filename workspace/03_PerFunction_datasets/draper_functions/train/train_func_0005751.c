_send_init_msg()
{
	int rc, read_timeout;
	Buf buffer;
	dbd_init_msg_t req;
	int tmp_errno = SLURM_SUCCESS;

	errno = tmp_errno;

	buffer = init_buf(1024);
	pack16((uint16_t) DBD_INIT, buffer);
	if (!slurmdbd_cluster) {
		debug("No ClusterName set.");
		slurmdbd_cluster = slurm_get_cluster_name();
	}
	req.cluster_name = slurmdbd_cluster;
	req.rollback = rollback_started;
	req.version  = SLURM_PROTOCOL_VERSION;
	slurmdbd_pack_init_msg(&req, SLURM_PROTOCOL_VERSION, buffer,
			       slurmdbd_auth_info);


	tmp_errno = errno;

	rc = _send_msg(buffer);
	free_buf(buffer);
	if (rc != SLURM_SUCCESS) {
		error("slurmdbd: Sending DBD_INIT message: %d: %m", rc);
		return rc;
	}

	read_timeout = slurm_get_msg_timeout() * 1000;
	rc = _get_return_code(SLURM_PROTOCOL_VERSION, read_timeout);
	if (tmp_errno)
		errno = tmp_errno;
	else if (rc != SLURM_SUCCESS)
		errno = rc;
	return rc;
}
