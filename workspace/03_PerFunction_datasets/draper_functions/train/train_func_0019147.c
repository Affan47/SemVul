_one_step_complete_msg(stepd_step_rec_t *job, int first, int last)
{
	slurm_msg_t req;
	step_complete_msg_t msg;
	int rc = -1;
	int retcode;
	int i;
	uint16_t port = 0;
	char ip_buf[16];
	static bool acct_sent = false;

	debug2("_one_step_complete_msg: first=%d, last=%d", first, last);

	memset(&msg, 0, sizeof(step_complete_msg_t));
	msg.job_id = job->jobid;
	msg.job_step_id = job->stepid;
	msg.range_first = first;
	msg.range_last = last;
	msg.step_rc = step_complete.step_rc;
	msg.jobacct = jobacctinfo_create(NULL);

	if (!acct_sent) {
		jobacctinfo_aggregate(step_complete.jobacct, job->jobacct);
		jobacctinfo_getinfo(step_complete.jobacct,
				    JOBACCT_DATA_TOTAL, msg.jobacct,
				    SLURM_PROTOCOL_VERSION);
		acct_sent = true;
	}

	slurm_msg_t_init(&req);
	req.msg_type = REQUEST_STEP_COMPLETE;
	req.data = &msg;
	req.address = step_complete.parent_addr;


	if (step_complete.parent_rank != -1) {
		debug3("Rank %d sending complete to rank %d, range %d to %d",
		       step_complete.rank, step_complete.parent_rank,
		       first, last);


		for (i = 0; i < REVERSE_TREE_PARENT_RETRY; i++) {
			if (i)
				sleep(1);
			retcode = slurm_send_recv_rc_msg_only_one(&req, &rc, 0);
			if ((retcode == 0) && (rc == 0))
				goto finished;
		}

		debug3("Rank %d sending complete to slurmctld instead, range "
		       "%d to %d", step_complete.rank, first, last);
	} else {

		debug3("Rank %d sending complete to slurmctld, range %d to %d",
		       step_complete.rank, first, last);
	}


	i = 1;
	while (slurm_send_recv_controller_rc_msg(&req, &rc) < 0) {
		if (i++ == 1) {
			slurm_get_ip_str(&step_complete.parent_addr, &port,
					 ip_buf, sizeof(ip_buf));
			error("Rank %d failed sending step completion message "
			      "directly to slurmctld (%s:%u), retrying",
			      step_complete.rank, ip_buf, port);
		}
		sleep(60);
	}
	if (i > 1) {
		info("Rank %d sent step completion message directly to "
		     "slurmctld (%s:%u)", step_complete.rank, ip_buf, port);
	}

finished:
	jobacctinfo_destroy(msg.jobacct);
}
