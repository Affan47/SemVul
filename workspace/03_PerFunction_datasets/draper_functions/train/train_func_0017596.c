_send_launch_resp(stepd_step_rec_t *job, int rc)
{
	int i;
	slurm_msg_t resp_msg;
	launch_tasks_response_msg_t resp;
	srun_info_t *srun = list_peek(job->sruns);

	if (job->batch)
		return;

	debug("Sending launch resp rc=%d", rc);

	slurm_msg_t_init(&resp_msg);
	resp_msg.address	= srun->resp_addr;
	resp_msg.data		= &resp;
	resp_msg.msg_type	= RESPONSE_LAUNCH_TASKS;

	resp.node_name		= xstrdup(job->node_name);
	resp.return_code	= rc;
	resp.count_of_pids	= job->node_tasks;

	resp.local_pids = xmalloc(job->node_tasks * sizeof(*resp.local_pids));
	resp.task_ids = xmalloc(job->node_tasks * sizeof(*resp.task_ids));
	for (i = 0; i < job->node_tasks; i++) {
		resp.local_pids[i] = job->task[i]->pid;
		resp.task_ids[i] = job->task[i]->gtid;
	}

	if (_send_launch_resp_msg(&resp_msg, job->nnodes) != SLURM_SUCCESS)
		error("failed to send RESPONSE_LAUNCH_TASKS: %m");

	xfree(resp.local_pids);
	xfree(resp.task_ids);
	xfree(resp.node_name);
}
