as_pg_remove_clusters(pgsql_conn_t *pg_conn, uint32_t uid,
		      slurmdb_cluster_cond_t *cluster_cond)
{
	DEF_VARS;
	List ret_list = NULL, job_list = NULL;
	int rc = SLURM_SUCCESS, has_jobs;
	char *cond = NULL, *user_name = NULL;
	time_t now = time(NULL);

	if(!cluster_cond) {
		error("as/pg: remove_clusters: we need something to remove");
		return NULL;
	}
	if(check_db_connection(pg_conn) != SLURM_SUCCESS)
		return NULL;

	concat_cond_list(cluster_cond->cluster_list, NULL, "name", &cond);
	if(!cond) {
		error("as/pg: remove_clusters: nothing to remove");
		return NULL;
	}
	query = xstrdup_printf("SELECT name FROM %s WHERE deleted=0 %s;",
			       cluster_table, cond);
	xfree(cond);
	result = DEF_QUERY_RET;
	if (!result) {
		error("as/pg: remove_clusters: failed to get cluster names");
		return NULL;
	}

	ret_list = list_create(slurm_destroy_char);
	if (PQntuples(result) == 0) {
		PQclear(result);
		errno = SLURM_NO_CHANGE_IN_DATA;
		debug3("didn't effect anything");

		return ret_list;
	}

	user_name = uid_to_string((uid_t)uid);
	rc = 0;
	FOR_EACH_ROW {
		char *cluster = ROW(0);

		job_list = _get_cluster_running_jobs(pg_conn, cluster);
		if (job_list)
			break;

		has_jobs = _cluster_has_jobs(pg_conn, cluster);

		if (!has_jobs)
			query = xstrdup_printf(
				"DELETE FROM %s WHERE creation_time>%ld AND "
				"name='%s';", cluster_table,
				(now - DELETE_SEC_BACK), cluster);
		xstrfmtcat(query,
			   "UPDATE %s SET mod_time=%ld, deleted=1 WHERE "
			   "deleted=0 AND name='%s';", cluster_table, now,
			   cluster);
		xstrfmtcat(query,
			   "INSERT INTO %s (timestamp, action, name, actor) "
			   "VALUES (%ld, %d, '%s', '%s');", txn_table, now,
			   (int)DBD_REMOVE_CLUSTERS, cluster, user_name);

		rc = DEF_QUERY_RET_RC;
		if (rc != SLURM_SUCCESS)
			break;

		rc = _remove_cluster_tables(pg_conn, cluster);
		if (rc != SLURM_SUCCESS)
			break;

		list_append(ret_list, xstrdup(cluster));
		addto_update_list(pg_conn->update_list, SLURMDB_REMOVE_CLUSTER,
				  xstrdup(cluster));
		pg_conn->cluster_changed = 1;
	} END_EACH_ROW;
	PQclear(result);

	if (job_list) {
		reset_pgsql_conn(pg_conn);
		list_destroy(ret_list);
		error("as/pg: remove_clusters: jobs running on cluster");
		errno = ESLURM_JOBS_RUNNING_ON_ASSOC;
		return job_list;
	}
	if (rc != SLURM_SUCCESS) {
		reset_pgsql_conn(pg_conn);
		list_destroy(ret_list);
		ret_list = NULL;
	}
	return ret_list;
}
