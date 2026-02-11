dpm_decode_pfr_entry(res, row, lock, rec_addr, pfr_entry)
PGresult *res;
int row;
int lock;
dpm_dbrec_addr *rec_addr;
struct dpm_put_filereq *pfr_entry;
{
	int i = 0;

	if (lock)
		strcpy (*rec_addr, PQgetvalue (res, row, i++));
	strcpy (pfr_entry->r_token, PQgetvalue (res, row, i++));
	pfr_entry->f_ordinal = atoi (PQgetvalue (res, row, i++));
	strcpy (pfr_entry->to_surl, PQgetvalue (res, row, i++));
	strcpy (pfr_entry->protocol, PQgetvalue (res, row, i++));
	pfr_entry->lifetime = atoi (PQgetvalue (res, row, i++));
	pfr_entry->f_lifetime = atoi (PQgetvalue (res, row, i++));
	pfr_entry->f_type = *(PQgetvalue (res, row, i++));
	strcpy (pfr_entry->s_token, PQgetvalue (res, row, i++));
	pfr_entry->ret_policy = *(PQgetvalue (res, row, i++));
	pfr_entry->ac_latency = *(PQgetvalue (res, row, i++));
	pfr_entry->requested_size = strtou64 (PQgetvalue (res, row, i++));
	strcpy (pfr_entry->server, PQgetvalue (res, row, i++));
	strcpy (pfr_entry->pfn, PQgetvalue (res, row, i++));
	pfr_entry->actual_size = strtou64 (PQgetvalue (res, row, i++));
	pfr_entry->status = atoi (PQgetvalue (res, row, i++));
	strcpy (pfr_entry->errstring, PQgetvalue (res, row, i));
}
