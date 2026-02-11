dpm_update_pool_entry (dbfd, rec_addr, pool_entry)
struct dpm_dbfd *dbfd;
dpm_dbrec_addr *rec_addr;
struct dpm_pool *pool_entry;
{
	char defsize_str[21];
	char func[22];
	char groups[256];
	PGresult *res;
	char sql_stmt[1024];
	static char update_stmt[] =
		"UPDATE dpm_pool SET \
		DEFSIZE = %s, GC_START_THRESH = %d, GC_STOP_THRESH = %d, \
		DEF_LIFETIME = %d, DEFPINTIME = %d, MAX_LIFETIME = %d, \
		MAXPINTIME = %d, \
		FSS_POLICY = '%s', GC_POLICY = '%s', MIG_POLICY = '%s', \
		RS_POLICY = '%s', GROUPS = '%s', RET_POLICY = '%c', S_TYPE = '%c' \
		WHERE ROWID = %s";

	strcpy (func, "dpm_update_pool_entry");
	sprintf (sql_stmt, update_stmt,
	    u64tostr (pool_entry->defsize, defsize_str, -1),
	    pool_entry->gc_start_thresh, pool_entry->gc_stop_thresh,
	    pool_entry->def_lifetime, pool_entry->defpintime,
	    pool_entry->max_lifetime, pool_entry->maxpintime,
	    pool_entry->fss_policy, pool_entry->gc_policy,
	    pool_entry->mig_policy, pool_entry->rs_policy,
	    Cencode_groups (pool_entry->nbgids, pool_entry->gids, groups, sizeof(groups)),
	    pool_entry->ret_policy, pool_entry->s_type, *rec_addr);

	res = PQexec (dbfd->Pconn, sql_stmt);
	if (PQresultStatus (res) != PGRES_COMMAND_OK) {
		dpm_libpq_error (func, "UPDATE", res, dbfd);
		return (-1);
	}
	PQclear (res);
	return (0);
}
