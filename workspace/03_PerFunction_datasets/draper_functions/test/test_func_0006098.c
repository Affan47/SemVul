_modify_reservation(slurmdbd_conn_t *slurmdbd_conn,
			       Buf in_buffer, Buf *out_buffer, uint32_t *uid)
{
	int rc = SLURM_SUCCESS;
	dbd_rec_msg_t *rec_msg = NULL;
	char *comment = NULL;

	if ((*uid != slurmdbd_conf->slurm_user_id && *uid != 0)) {
		comment = "DBD_MODIFY_RESV message from invalid uid";
		error("CONN:%u %s %u",
		      slurmdbd_conn->newsockfd, comment, *uid);
		rc = ESLURM_ACCESS_DENIED;
		goto end_it;
	}
	if (slurmdbd_unpack_rec_msg(&rec_msg, slurmdbd_conn->rpc_version,
				    DBD_MODIFY_RESV, in_buffer)
	    != SLURM_SUCCESS) {
		comment = "Failed to unpack DBD_MODIFY_RESV message";
		error("CONN:%u %s", slurmdbd_conn->newsockfd, comment);
		rc = SLURM_ERROR;
		goto end_it;
	}
	debug2("DBD_MODIFY_RESV: called");

	rc = acct_storage_g_modify_reservation(slurmdbd_conn->db_conn,
					       rec_msg->rec);

end_it:
	slurmdbd_free_rec_msg(rec_msg, DBD_MODIFY_RESV);
	*out_buffer = make_dbd_rc_msg(slurmdbd_conn->rpc_version,
				      rc, comment, DBD_MODIFY_RESV);
	return rc;
}
