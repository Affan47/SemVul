allocate_nodes(bool handle_signals)
{
	resource_allocation_response_msg_t *resp = NULL;
	job_desc_msg_t *j = job_desc_msg_create_from_opts();
	slurm_allocation_callbacks_t callbacks;
	int i;

	if (!j)
		return NULL;


	if ((j->job_id != NO_VAL) && !opt.jobid_set) {
		info("WARNING: Creating SLURM job allocation from within "
		     "another allocation");
		info("WARNING: You are attempting to initiate a second job");
		if (!opt.jobid_set)
			j->job_id = NO_VAL;
	}
	callbacks.ping = _ping_handler;
	callbacks.timeout = _timeout_handler;
	callbacks.job_complete = _job_complete_handler;
	callbacks.job_suspend = NULL;
	callbacks.user_msg = _user_msg_handler;
	callbacks.node_fail = _node_fail_handler;


	msg_thr = slurm_allocation_msg_thr_create(&j->other_port, &callbacks);


	if (handle_signals) {
		xsignal_unblock(sig_array);
		for (i = 0; sig_array[i]; i++)
			xsignal(sig_array[i], _signal_while_allocating);
	}

	while (!resp) {
		resp = slurm_allocate_resources_blocking(j, opt.immediate,
							 _set_pending_job_id);
		if (destroy_job) {

			break;
		} else if (!resp && !_retry()) {
			break;
		}
	}

	if (resp && !destroy_job) {


		pending_job_id = resp->job_id;
#ifdef HAVE_BG
		if (!_wait_bluegene_block_ready(resp)) {
			if(!destroy_job)
				error("Something is wrong with the "
				      "boot of the block.");
			goto relinquish;
		}
#else
		if (!_wait_nodes_ready(resp)) {
			if (!destroy_job)
				error("Something is wrong with the "
				      "boot of the nodes.");
			goto relinquish;
		}
#endif
	} else if (destroy_job) {
		goto relinquish;
	}

	if (handle_signals)
		xsignal_block(sig_array);

	job_desc_msg_destroy(j);

	return resp;

relinquish:

	slurm_free_resource_allocation_response_msg(resp);
	if (!destroy_job)
		slurm_complete_job(resp->job_id, 1);
	exit(error_exit);
	return NULL;
}
