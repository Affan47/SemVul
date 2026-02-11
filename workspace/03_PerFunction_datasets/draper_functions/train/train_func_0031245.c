mysql_db_query(mysql_conn_t *mysql_conn, char *query)
{
	int rc = SLURM_SUCCESS;

	if (!mysql_conn || !mysql_conn->db_conn)
		fatal("You haven't inited this storage yet.");
	slurm_mutex_lock(&mysql_conn->lock);
	rc = _mysql_query_internal(mysql_conn->db_conn, query);
	slurm_mutex_unlock(&mysql_conn->lock);
	return rc;
}
