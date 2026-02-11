_get_cluster_usage(mysql_conn_t *mysql_conn, uid_t uid,
			      slurmdb_cluster_rec_t *cluster_rec,
			      slurmdbd_msg_type_t type,
			      time_t start, time_t end)
{
	int rc = SLURM_SUCCESS;
	int i=0;
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	char *tmp = NULL;
	char *my_usage_table = cluster_day_table;
	char *query = NULL;
	char *cluster_req_inx[] = {
		"alloc_cpu_secs",
		"down_cpu_secs",
		"pdown_cpu_secs",
		"idle_cpu_secs",
		"resv_cpu_secs",
		"over_cpu_secs",
		"cpu_count",
		"time_start"
	};

	enum {
		CLUSTER_ACPU,
		CLUSTER_DCPU,
		CLUSTER_PDCPU,
		CLUSTER_ICPU,
		CLUSTER_RCPU,
		CLUSTER_OCPU,
		CLUSTER_CPU_COUNT,
		CLUSTER_START,
		CLUSTER_COUNT
	};

	if (!cluster_rec->name || !cluster_rec->name[0]) {
		error("We need a cluster name to set data for");
		return SLURM_ERROR;
	}

	if (set_usage_information(&my_usage_table, type, &start, &end)
	    != SLURM_SUCCESS) {
		return SLURM_ERROR;
	}

	xfree(tmp);
	i=0;
	xstrfmtcat(tmp, "%s", cluster_req_inx[i]);
	for(i=1; i<CLUSTER_COUNT; i++) {
		xstrfmtcat(tmp, ", %s", cluster_req_inx[i]);
	}

	query = xstrdup_printf(
		"select %s from \"%s_%s\" where (time_start < %ld "
		"&& time_start >= %ld)",
		tmp, cluster_rec->name, my_usage_table, end, start);

	xfree(tmp);
	debug4("%d(%s:%d) query\n%s",
	       mysql_conn->conn, THIS_FILE, __LINE__, query);
	if (!(result = mysql_db_query_ret(
		      mysql_conn, query, 0))) {
		xfree(query);
		return SLURM_ERROR;
	}
	xfree(query);

	if (!cluster_rec->accounting_list)
		cluster_rec->accounting_list =
			list_create(slurmdb_destroy_cluster_accounting_rec);

	while ((row = mysql_fetch_row(result))) {
		slurmdb_cluster_accounting_rec_t *accounting_rec =
			xmalloc(sizeof(slurmdb_cluster_accounting_rec_t));
		accounting_rec->alloc_secs = slurm_atoull(row[CLUSTER_ACPU]);
		accounting_rec->down_secs = slurm_atoull(row[CLUSTER_DCPU]);
		accounting_rec->pdown_secs = slurm_atoull(row[CLUSTER_PDCPU]);
		accounting_rec->idle_secs = slurm_atoull(row[CLUSTER_ICPU]);
		accounting_rec->over_secs = slurm_atoull(row[CLUSTER_OCPU]);
		accounting_rec->resv_secs = slurm_atoull(row[CLUSTER_RCPU]);
		accounting_rec->cpu_count = slurm_atoul(row[CLUSTER_CPU_COUNT]);
		accounting_rec->period_start = slurm_atoul(row[CLUSTER_START]);
		list_append(cluster_rec->accounting_list, accounting_rec);
	}
	mysql_free_result(result);

	return rc;
}
