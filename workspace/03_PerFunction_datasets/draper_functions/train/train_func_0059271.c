_unpack_job_step_info_req_msg(job_step_info_request_msg_t ** msg, Buf buffer,
			      uint16_t protocol_version)
{
	job_step_info_request_msg_t *job_step_info;

	job_step_info = xmalloc(sizeof(job_step_info_request_msg_t));
	*msg = job_step_info;

	safe_unpack_time(&job_step_info->last_update, buffer);
	safe_unpack32(&job_step_info->job_id, buffer);
	safe_unpack32(&job_step_info->step_id, buffer);
	safe_unpack16(&job_step_info->show_flags, buffer);
	return SLURM_SUCCESS;

unpack_error:
	slurm_free_job_step_info_request_msg(job_step_info);
	*msg = NULL;
	return SLURM_ERROR;
}
