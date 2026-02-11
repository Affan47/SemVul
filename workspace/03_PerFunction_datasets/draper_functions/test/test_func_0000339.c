acct_storage_p_roll_usage(void *db_conn,
				     time_t sent_start, time_t sent_end,
				     uint16_t archive_data)
{
	slurmdbd_msg_t req;
	dbd_roll_usage_msg_t get_msg;
	int rc, resp_code;

	memset(&get_msg, 0, sizeof(dbd_roll_usage_msg_t));
	get_msg.end = sent_end;
	get_msg.start = sent_start;
	get_msg.archive_data = archive_data;

	req.msg_type = DBD_ROLL_USAGE;

	req.data = &get_msg;

	rc = slurm_send_slurmdbd_recv_rc_msg(SLURM_PROTOCOL_VERSION,
					     &req, &resp_code);

	if (resp_code != SLURM_SUCCESS)
		rc = resp_code;
	else
		info("SUCCESS");
	return rc;
}
