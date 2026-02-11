abort_job_on_node(uint32_t job_id, struct job_record *job_ptr, char *node_name)
{
	agent_arg_t *agent_info;
	kill_job_msg_t *kill_req;

	kill_req = xmalloc(sizeof(kill_job_msg_t));
	kill_req->job_id	= job_id;
	kill_req->step_id	= NO_VAL;
	kill_req->time          = time(NULL);
	kill_req->nodes		= xstrdup(node_name);
	if (job_ptr) {
		kill_req->start_time = job_ptr->start_time;
		kill_req->select_jobinfo =
			select_g_select_jobinfo_copy(job_ptr->select_jobinfo);
		kill_req->spank_job_env = xduparray(job_ptr->spank_job_env_size,
						    job_ptr->spank_job_env);
		kill_req->spank_job_env_size = job_ptr->spank_job_env_size;
	} else {

	}

	agent_info = xmalloc(sizeof(agent_arg_t));
	agent_info->node_count	= 1;
	agent_info->retry	= 0;
	agent_info->hostlist	= hostlist_create(node_name);
#ifdef HAVE_FRONT_END
	debug("Aborting job %u on front end node %s", job_id, node_name);
#else

	debug("Aborting job %u on node %s", job_id, node_name);
#endif
	agent_info->msg_type	= REQUEST_ABORT_JOB;
	agent_info->msg_args	= kill_req;

	agent_queue_request(agent_info);
}
