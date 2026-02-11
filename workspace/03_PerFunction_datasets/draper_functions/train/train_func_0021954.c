_get_user_running_jobs(pgsql_conn_t *pg_conn, char *assoc_cond)
{
	DEF_VARS;
	List job_list = NULL;
	char *job = NULL;
	char *fields = "t0.id_job,t1.acct,t1.user_name,t1.partition";

	FOR_EACH_CLUSTER(NULL) {
		if (query)
			xstrcat(query, " UNION ");
		xstrfmtcat(
			query, "SELECT DISTINCT %s, '%s' FROM %s.%s AS t0, "
			"%s.%s AS t1 WHERE (%s) AND "
			"t0.id_assoc=t1.id_assoc AND t0.state=%d AND "
			"t0.time_end=0", fields, cluster_name, cluster_name,
			job_table, cluster_name, assoc_table, assoc_cond,
			JOB_RUNNING);
	} END_EACH_CLUSTER;

	result = DEF_QUERY_RET;
	if (!result)
		return NULL;

	FOR_EACH_ROW {
		if (ISEMPTY(2)) {
			error("how could job %s running on non-user "
			      "assoc <%s, %s, '', ''>", ROW(0),
			      ROW(4), ROW(1));
			continue;
		}
		job = xstrdup_printf(
			"JobID = %-10s C = %-10s A = %-10s U = %-9s",
			ROW(0), ROW(4), ROW(1), ROW(2));
		if(!ISEMPTY(3))
			xstrfmtcat(job, " P = %s", ROW(3));
		if (!job_list)
			job_list = list_create(slurm_destroy_char);
		list_append(job_list, job);
	} END_EACH_ROW;
	PQclear(result);
	return job_list;
}
