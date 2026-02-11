_job_will_run (job_desc_msg_t *req)
{
	slurm_msg_t req_msg, resp_msg;
	will_run_response_msg_t *will_run_resp;
	int rc;
	char buf[64];
	char *type = "processors";
	local_cluster_rec_t *local_cluster = NULL;


	slurm_msg_t_init(&req_msg);
	req_msg.msg_type = REQUEST_JOB_WILL_RUN;
	req_msg.data     = req;

	rc = slurm_send_recv_controller_msg(&req_msg, &resp_msg);

	if (rc < 0) {
		slurm_seterrno(SLURM_SOCKET_ERROR);
		return NULL;
	}
	switch (resp_msg.msg_type) {
	case RESPONSE_SLURM_RC:
		rc = ((return_code_msg_t *) resp_msg.data)->return_code;
		slurm_free_return_code_msg(resp_msg.data);
		if (rc)
			slurm_seterrno(rc);
		break;
	case RESPONSE_JOB_WILL_RUN:
		if (working_cluster_rec->flags & CLUSTER_FLAG_BG)
			type = "cnodes";
		will_run_resp = (will_run_response_msg_t *) resp_msg.data;
		slurm_make_time_str(&will_run_resp->start_time,
				    buf, sizeof(buf));
		debug("Job %u to start at %s on cluster %s using %u %s on %s",
		      will_run_resp->job_id, buf, working_cluster_rec->name,
		      will_run_resp->proc_cnt, type,
		      will_run_resp->node_list);
		local_cluster = xmalloc(sizeof(local_cluster_rec_t));
		local_cluster->cluster_rec = working_cluster_rec;
		local_cluster->start_time = will_run_resp->start_time;
		if (will_run_resp->preemptee_job_id) {
			local_cluster->preempt_cnt =
				list_count(will_run_resp->preemptee_job_id);
			if (opt.verbose >= LOG_LEVEL_DEBUG) {
				ListIterator itr;
				uint32_t *job_id_ptr;
				char *job_list = NULL, *sep = "";
				itr = list_iterator_create(will_run_resp->
							   preemptee_job_id);
				while ((job_id_ptr = list_next(itr))) {
					if (job_list)
						sep = ",";
					xstrfmtcat(job_list, "%s%u",
						   sep, *job_id_ptr);
				}
				debug("  Preempts: %s", job_list);
				xfree(job_list);
			}
		}

		slurm_free_will_run_response_msg(will_run_resp);
		break;
	default:
		slurm_seterrno(SLURM_UNEXPECTED_MSG_ERROR);
		return NULL;
		break;
	}
	return local_cluster;
}
