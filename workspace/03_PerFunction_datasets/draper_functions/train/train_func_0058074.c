js_pg_archive(pgsql_conn_t *pg_conn, slurmdb_archive_cond_t *arch_cond)
{
	int rc = SLURM_SUCCESS;
	List cluster_list = NULL;

	if(!arch_cond) {
		error("No arch_cond was given to archive from. returning");
		return SLURM_ERROR;
	}

	if (check_db_connection(pg_conn) != SLURM_SUCCESS)
		return ESLURM_DB_CONNECTION;

	if (arch_cond->job_cond)
		cluster_list = arch_cond->job_cond->cluster_list;

	FOR_EACH_CLUSTER(cluster_list) {
		rc = _execute_archive(pg_conn, cluster_name, arch_cond);
		if (rc != SLURM_SUCCESS)
			break;
	} END_EACH_CLUSTER;

	return rc;
}
