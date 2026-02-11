_unpack_job_notify(job_notify_msg_t **msg_ptr, Buf buffer,
			       uint16_t protocol_version)
{
	uint32_t uint32_tmp;
	job_notify_msg_t *msg;

	xassert(msg_ptr);

	msg = xmalloc(sizeof(job_notify_msg_t));

	safe_unpack32(&msg->job_id,      buffer);
	safe_unpack32(&msg->job_step_id, buffer);
	safe_unpackstr_xmalloc(&msg->message, &uint32_tmp, buffer);

	*msg_ptr = msg;
	return SLURM_SUCCESS;

unpack_error:
	slurm_free_job_notify_msg(msg);
	*msg_ptr = NULL;
	return SLURM_ERROR;
}
