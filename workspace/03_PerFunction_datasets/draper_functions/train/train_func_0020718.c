mysql_db_insert_ret_id(mysql_conn_t *mysql_conn, char *query)
{
	int new_id = 0;

	slurm_mutex_lock(&mysql_conn->lock);
	if (_mysql_query_internal(mysql_conn->db_conn, query) != SLURM_ERROR)  {
		new_id = mysql_insert_id(mysql_conn->db_conn);
		if (!new_id) {

			error("We should have gotten a new id: %s",
			      mysql_error(mysql_conn->db_conn));
		}
	}
	slurm_mutex_unlock(&mysql_conn->lock);
	return new_id;

}
