_purge_agent_args(agent_arg_t *agent_arg_ptr)
{
	if (agent_arg_ptr == NULL)
		return;

	hostlist_destroy(agent_arg_ptr->hostlist);
	xfree(agent_arg_ptr->addr);
	if (agent_arg_ptr->msg_args) {
		if (agent_arg_ptr->msg_type == REQUEST_BATCH_JOB_LAUNCH)
			slurmctld_free_batch_job_launch_msg(agent_arg_ptr->
							    msg_args);
		else if (agent_arg_ptr->msg_type ==
				RESPONSE_RESOURCE_ALLOCATION)
			slurm_free_resource_allocation_response_msg(
					agent_arg_ptr->msg_args);
		else if ((agent_arg_ptr->msg_type == REQUEST_ABORT_JOB)      ||
			 (agent_arg_ptr->msg_type == REQUEST_TERMINATE_JOB)  ||
			 (agent_arg_ptr->msg_type == REQUEST_KILL_PREEMPTED) ||
			 (agent_arg_ptr->msg_type == REQUEST_KILL_TIMELIMIT))
			slurm_free_kill_job_msg(agent_arg_ptr->msg_args);
		else if (agent_arg_ptr->msg_type == SRUN_USER_MSG)
			slurm_free_srun_user_msg(agent_arg_ptr->msg_args);
		else if (agent_arg_ptr->msg_type == SRUN_EXEC)
			slurm_free_srun_exec_msg(agent_arg_ptr->msg_args);
		else if (agent_arg_ptr->msg_type == SRUN_NODE_FAIL)
			slurm_free_srun_node_fail_msg(agent_arg_ptr->msg_args);
		else if (agent_arg_ptr->msg_type == SRUN_STEP_MISSING)
			slurm_free_srun_step_missing_msg(
				agent_arg_ptr->msg_args);
		else if (agent_arg_ptr->msg_type == SRUN_STEP_SIGNAL)
			slurm_free_job_step_kill_msg(
				agent_arg_ptr->msg_args);
		else if (agent_arg_ptr->msg_type == REQUEST_JOB_NOTIFY)
			slurm_free_job_notify_msg(agent_arg_ptr->msg_args);
		else if (agent_arg_ptr->msg_type == REQUEST_SUSPEND_INT)
			slurm_free_suspend_int_msg(agent_arg_ptr->msg_args);
		else
			xfree(agent_arg_ptr->msg_args);
	}
	xfree(agent_arg_ptr);
}
