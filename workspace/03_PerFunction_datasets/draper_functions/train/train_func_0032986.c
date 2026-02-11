slurm_ckpt_pack_job(check_jobinfo_t jobinfo, Buf buffer,
			       uint16_t protocol_version)
{
	struct check_job_info *check_ptr =
		(struct check_job_info *)jobinfo;

	if (protocol_version >= SLURM_2_3_PROTOCOL_VERSION) {
		pack16(check_ptr->disabled, buffer);
		pack16(check_ptr->reply_cnt, buffer);
		pack16(check_ptr->wait_time, buffer);

		pack32(check_ptr->error_code, buffer);
		packstr(check_ptr->error_msg, buffer);
		pack_time(check_ptr->time_stamp, buffer);
	}

	return SLURM_SUCCESS;
}
