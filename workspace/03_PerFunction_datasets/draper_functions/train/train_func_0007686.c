_notify_slurmctld_nodes(agent_info_t *agent_ptr,
				    int no_resp_cnt, int retry_cnt)
{
	ListIterator itr = NULL;
	ret_data_info_t *ret_data_info = NULL;
	state_t state;
	int is_ret_list = 1;

	slurmctld_lock_t node_write_lock =
	    { READ_LOCK, WRITE_LOCK, WRITE_LOCK, NO_LOCK };
	thd_t *thread_ptr = agent_ptr->thread_struct;
	int i;


	if (no_resp_cnt) {

		lock_slurmctld(node_write_lock);
		if (agent_ptr->msg_type == REQUEST_BATCH_JOB_LAUNCH) {

			batch_job_launch_msg_t *launch_msg_ptr =
					*agent_ptr->msg_args_pptr;
			uint32_t job_id = launch_msg_ptr->job_id;
			job_complete(job_id, 0, true, false, 0);
		}
		unlock_slurmctld(node_write_lock);
	}
	if (retry_cnt && agent_ptr->retry)
		_queue_agent_retry(agent_ptr, retry_cnt);


	lock_slurmctld(node_write_lock);
	for (i = 0; i < agent_ptr->thread_count; i++) {
		char *down_msg, *node_names;
		if (!thread_ptr[i].ret_list) {
			state = thread_ptr[i].state;
			is_ret_list = 0;
			goto switch_on_state;
		}
		is_ret_list = 1;

		itr = list_iterator_create(thread_ptr[i].ret_list);
		while ((ret_data_info = list_next(itr))) {
			state = ret_data_info->err;
		switch_on_state:
			switch(state) {
			case DSH_NO_RESP:
				if (!is_ret_list) {
					node_not_resp(thread_ptr[i].nodelist,
						      thread_ptr[i].
						      start_time);
				} else {
					node_not_resp(ret_data_info->node_name,
						      thread_ptr[i].start_time);
				}
				break;
			case DSH_FAILED:
				if (is_ret_list)
					node_names = ret_data_info->node_name;
				else
					node_names = thread_ptr[i].nodelist;
#ifdef HAVE_FRONT_END
				down_msg = "";
#else
				set_node_down(node_names,
					      "Prolog/Epilog failure");
				down_msg = ", set to state DOWN";
#endif
				error("Prolog/Epilog failure on nodes %s%s",
				      node_names, down_msg);
				break;
			case DSH_DONE:
				if (!is_ret_list)
					node_did_resp(thread_ptr[i].nodelist);
				else
					node_did_resp(ret_data_info->node_name);
				break;
			default:
				if (!is_ret_list) {
					error("unknown state returned for %s",
					      thread_ptr[i].nodelist);
				} else {
					error("unknown state returned for %s",
					      ret_data_info->node_name);
				}
				break;
			}
			if (!is_ret_list)
				goto finished;
		}
		list_iterator_destroy(itr);
finished:	;
	}
	unlock_slurmctld(node_write_lock);
	if (run_scheduler) {
		run_scheduler = false;

		if (schedule(0))	{
			schedule_job_save();
			schedule_node_save();
		}
	}
	if ((agent_ptr->msg_type == REQUEST_PING) ||
	    (agent_ptr->msg_type == REQUEST_HEALTH_CHECK) ||
	    (agent_ptr->msg_type == REQUEST_ACCT_GATHER_UPDATE) ||
	    (agent_ptr->msg_type == REQUEST_NODE_REGISTRATION_STATUS))
		ping_end();
}
