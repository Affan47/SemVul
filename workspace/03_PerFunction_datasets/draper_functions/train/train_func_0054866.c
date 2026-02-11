acct_storage_p_remove_reservation(void *db_conn,
					     slurmdb_reservation_rec_t *resv)
{
	slurmdbd_msg_t req;
	dbd_rec_msg_t get_msg;
	int rc, resp_code;

	memset(&get_msg, 0, sizeof(dbd_rec_msg_t));
	get_msg.rec = resv;

	req.msg_type = DBD_REMOVE_RESV;
	req.data = &get_msg;

	rc = slurm_send_slurmdbd_recv_rc_msg(SLURM_PROTOCOL_VERSION,
					     &req, &resp_code);

	if ((rc == SLURM_SUCCESS) && (resp_code != SLURM_SUCCESS))
		rc = resp_code;

	return rc;
}
