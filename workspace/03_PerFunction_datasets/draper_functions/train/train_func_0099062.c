_handle_ping(struct allocation_msg_thread *msg_thr,
			     slurm_msg_t *msg)
{
	srun_ping_msg_t *ping = (srun_ping_msg_t *)msg->data;
	debug3("received ping message");
	slurm_send_rc_msg(msg, SLURM_SUCCESS);

	if (msg_thr->callback.ping != NULL)
		(msg_thr->callback.ping)(ping);

	slurm_free_srun_ping_msg(msg->data);
}
