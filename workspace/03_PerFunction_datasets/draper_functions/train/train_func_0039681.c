_front_end_reg(
		slurm_node_registration_status_msg_t *reg_msg)
{
	front_end_record_t *front_end_ptr;
	uint16_t state_base, state_flags;
	time_t now = time(NULL);

	debug2("name:%s boot_time:%u up_time:%u",
	       reg_msg->node_name, (unsigned int) reg_msg->slurmd_start_time,
	       reg_msg->up_time);

	front_end_ptr = find_front_end_record(reg_msg->node_name);
	if (front_end_ptr == NULL) {
		error("Registration message from unknown node %s",
		      reg_msg->node_name);
		return NULL;
	}

	front_end_ptr->boot_time = now - reg_msg->up_time;
	if (front_end_ptr->last_response &&
	    (front_end_ptr->boot_time > front_end_ptr->last_response)) {
		info("front end %s unexpectedly rebooted, "
		     "killing all previously running jobs running on it.",
		     reg_msg->node_name);
		(void) kill_job_by_front_end_name(front_end_ptr->name);
		reg_msg->job_count = 0;
	}

	front_end_ptr->last_response = now;
	front_end_ptr->slurmd_start_time = reg_msg->slurmd_start_time;
	state_base  = front_end_ptr->node_state & JOB_STATE_BASE;
	state_flags = front_end_ptr->node_state & JOB_STATE_FLAGS;
	if ((state_base == NODE_STATE_DOWN) &&
	    (!strncmp(front_end_ptr->reason, "Not responding", 14))) {
		error("front end node %s returned to service",
		      reg_msg->node_name);
		state_base = NODE_STATE_IDLE;
		xfree(front_end_ptr->reason);
		front_end_ptr->reason_time = (time_t) 0;
		front_end_ptr->reason_uid = 0;
	}
	if (state_base == NODE_STATE_UNKNOWN)
		state_base = NODE_STATE_IDLE;

	state_flags &= (~NODE_STATE_NO_RESPOND);

	front_end_ptr->node_state = state_base | state_flags;
	last_front_end_update = now;
	return front_end_ptr;
}
