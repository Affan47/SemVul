_archive_steps(pgsql_conn_t *pg_conn, char *cluster_name,
	       time_t period_end, char *arch_dir,
	       uint32_t archive_period)
{
	DEF_VARS;
	int rc;


	query = xstrdup_printf(
		"SELECT %s FROM %s.%s WHERE time_start<%ld AND time_end!=0 "
		"AND deleted=0 ORDER BY time_start ASC",
		step_archive_fields, cluster_name,
		step_table, (long)period_end);

	result = DEF_QUERY_RET;
	if (!result)
		return SLURM_ERROR;

	rc = _archive_record(result, cluster_name, period_end, arch_dir,
			     archive_period, DBD_STEP_START, "step");
	return rc;
}
