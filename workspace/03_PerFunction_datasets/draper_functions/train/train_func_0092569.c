mysql_db_commit(mysql_conn_t *mysql_conn)
{
	int rc = SLURM_SUCCESS;

	if (!mysql_conn->db_conn)
		return SLURM_ERROR;

	slurm_mutex_lock(&mysql_conn->lock);

	_clear_results(mysql_conn->db_conn);
	if (mysql_commit(mysql_conn->db_conn)) {
		error("mysql_commit failed: %d %s",
		      mysql_errno(mysql_conn->db_conn),
		      mysql_error(mysql_conn->db_conn));
		errno = mysql_errno(mysql_conn->db_conn);
		rc = SLURM_ERROR;
	}
	slurm_mutex_unlock(&mysql_conn->lock);
	return rc;
}
