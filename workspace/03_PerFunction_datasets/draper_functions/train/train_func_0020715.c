_shutdown_primary_controller(int wait_time)
{
	int rc;
	slurm_msg_t req;

	slurm_msg_t_init(&req);
	if ((slurmctld_conf.control_addr == NULL) ||
	    (slurmctld_conf.control_addr[0] == '\0')) {
		error("_shutdown_primary_controller: "
		      "no primary controller to shutdown");
		return SLURM_ERROR;
	}

	slurm_set_addr(&req.address, slurmctld_conf.slurmctld_port,
		       slurmctld_conf.control_addr);


	req.msg_type = REQUEST_CONTROL;

	if (slurm_send_recv_rc_msg_only_one(&req, &rc,
				(CONTROL_TIMEOUT * 1000)) < 0) {
		error("_shutdown_primary_controller:send/recv: %m");
		return SLURM_ERROR;
	}
	if (rc == ESLURM_DISABLED)
		debug("primary controller responding");
	else if (rc == 0) {
		debug("primary controller has relinquished control");
	} else {
		error("_shutdown_primary_controller: %s", slurm_strerror(rc));
		return SLURM_ERROR;
	}


	if (wait_time)
		sleep(wait_time);

	return SLURM_SUCCESS;
}
