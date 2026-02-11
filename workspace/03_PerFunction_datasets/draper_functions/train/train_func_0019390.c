dpm_decode_pool_entry(res, row, lock, rec_addr, pool_entry)
PGresult *res;
int row;
int lock;
dpm_dbrec_addr *rec_addr;
struct dpm_pool *pool_entry;
{
	int i = 0;

	if (lock)
		strcpy (*rec_addr, PQgetvalue (res, row, i++));
	strcpy (pool_entry->poolname, PQgetvalue (res, row, i++));
	pool_entry->defsize = strtou64 (PQgetvalue (res, row, i++));
	pool_entry->gc_start_thresh = atoi (PQgetvalue (res, row, i++));
	pool_entry->gc_stop_thresh = atoi (PQgetvalue (res, row, i++));
	pool_entry->def_lifetime = atoi (PQgetvalue (res, row, i++));
	pool_entry->defpintime = atoi (PQgetvalue (res, row, i++));
	pool_entry->max_lifetime = atoi (PQgetvalue (res, row, i++));
	pool_entry->maxpintime = atoi (PQgetvalue (res, row, i++));
	strcpy (pool_entry->fss_policy, PQgetvalue (res, row, i++));
	strcpy (pool_entry->gc_policy, PQgetvalue (res, row, i++));
	strcpy (pool_entry->mig_policy, PQgetvalue (res, row, i++));
	strcpy (pool_entry->rs_policy, PQgetvalue (res, row, i++));
	pool_entry->gids = Cdecode_groups (PQgetvalue (res, row, i++), &pool_entry->nbgids);
	pool_entry->ret_policy = *(PQgetvalue (res, row, i++));
	pool_entry->s_type = *(PQgetvalue (res, row, i));
}
