_flush_jobs(slurmdbd_conn_t *slurmdbd_conn,
		       Buf in_buffer, Buf *out_buffer, uint32_t *uid)
{
	dbd_cluster_cpus_msg_t *cluster_cpus_msg = NULL;
	int rc = SLURM_SUCCESS;
	char *comment = NULL;

	if ((*uid != slurmdbd_conf->slurm_user_id && *uid != 0)) {
		comment = "DBD_FLUSH_JOBS message from invalid uid";
		error("DBD_FLUSH_JOBS message from invalid uid %u", *uid);
		rc = ESLURM_ACCESS_DENIED;
		goto end_it;
	}
	if (slurmdbd_unpack_cluster_cpus_msg(
		    &cluster_cpus_msg, slurmdbd_conn->rpc_version, in_buffer)
	    != SLURM_SUCCESS) {
		comment = "Failed to unpack DBD_FLUSH_JOBS message";
		error("CONN:%u %s", slurmdbd_conn->newsockfd, comment);
		rc = SLURM_ERROR;
		goto end_it;
	}
	debug2("DBD_FLUSH_JOBS: called for %s",
	       slurmdbd_conn->cluster_name);

	rc = acct_storage_g_flush_jobs_on_cluster(
		slurmdbd_conn->db_conn,
		cluster_cpus_msg->event_time);
end_it:
	slurmdbd_free_cluster_cpus_msg(cluster_cpus_msg);
	*out_buffer = make_dbd_rc_msg(slurmdbd_conn->rpc_version,
				      rc, comment, DBD_FLUSH_JOBS);
	return rc;
}
