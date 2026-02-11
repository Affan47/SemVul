_rpc_signal_job(slurm_msg_t *msg)
{
	signal_job_msg_t *req = msg->data;
	uid_t req_uid = g_slurm_auth_get_uid(msg->auth_cred, NULL);
	long job_uid;
	List steps;
	ListIterator i;
	step_loc_t *stepd = NULL;
	int step_cnt  = 0;
	int fd;

#ifdef HAVE_XCPU
	if (!_slurm_authorized_user(req_uid)) {
		error("REQUEST_SIGNAL_JOB not supported with XCPU system");
		if (msg->conn_fd >= 0) {
			slurm_send_rc_msg(msg, ESLURM_NOT_SUPPORTED);
			if (slurm_close_accepted_conn(msg->conn_fd) < 0)
				error ("_rpc_signal_job: close(%d): %m",
				       msg->conn_fd);
			msg->conn_fd = -1;
		}
		return;
	}
#endif

	debug("_rpc_signal_job, uid = %d, signal = %d", req_uid, req->signal);
	job_uid = _get_job_uid(req->job_id);
	if (job_uid < 0)
		goto no_job;


	if ((req_uid != job_uid) && (!_slurm_authorized_user(req_uid))) {
		error("Security violation: kill_job(%u) from uid %d",
		      req->job_id, req_uid);
		if (msg->conn_fd >= 0) {
			slurm_send_rc_msg(msg, ESLURM_USER_ID_MISSING);
			if (slurm_close_accepted_conn(msg->conn_fd) < 0)
				error ("_rpc_signal_job: close(%d): %m",
				       msg->conn_fd);
			msg->conn_fd = -1;
		}
		return;
	}


	steps = stepd_available(conf->spooldir, conf->node_name);
	i = list_iterator_create(steps);
	while ((stepd = list_next(i))) {
		if (stepd->jobid != req->job_id) {

			debug3("Step from other job: jobid=%u (this jobid=%u)",
			       stepd->jobid, req->job_id);
			continue;
		}

		if (stepd->stepid == SLURM_BATCH_SCRIPT) {
			debug2("batch script itself not signalled");
			continue;
		}

		step_cnt++;

		fd = stepd_connect(stepd->directory, stepd->nodename,
				   stepd->jobid, stepd->stepid);
		if (fd == -1) {
			debug3("Unable to connect to step %u.%u",
			       stepd->jobid, stepd->stepid);
			continue;
		}

		debug2("  signal %d to job %u.%u",
		       req->signal, stepd->jobid, stepd->stepid);
		if (stepd_signal_container(fd, req->signal) < 0)
			debug("signal jobid=%u failed: %m", stepd->jobid);
		close(fd);
	}
	list_iterator_destroy(i);
	list_destroy(steps);

no_job:
	if (step_cnt == 0) {
		debug2("No steps in jobid %u to send signal %d",
		       req->job_id, req->signal);
	}


	if (msg->conn_fd >= 0) {
		slurm_send_rc_msg(msg, SLURM_SUCCESS);
		if (slurm_close_accepted_conn(msg->conn_fd) < 0)
			error ("_rpc_signal_job: close(%d): %m", msg->conn_fd);
		msg->conn_fd = -1;
	}
}
