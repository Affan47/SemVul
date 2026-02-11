_move_account(pgsql_conn_t *pg_conn, char *cluster, uint32_t *lft,
	      uint32_t *rgt, char *id, char *parent, time_t now)
{
	char * query = NULL;
	PGresult *result;
	int rc = SLURM_SUCCESS, plft = -1;

	plft = _get_parent_lft(pg_conn, cluster, parent);
	if (plft < 0)
		return ESLURM_INVALID_PARENT_ACCOUNT;

	if ((plft + 1 - *lft) == 0)
		return ESLURM_SAME_PARENT_ACCOUNT;

	query = xstrdup_printf(
		"SELECT * FROM %s.move_account(%d, %d, %d, %s, '%s', %ld);",
		cluster, plft, *lft, *rgt, id, parent, now);
	result = DEF_QUERY_RET;
	if (result) {
		*lft = atoi(PG_VAL(0));
		*rgt = atoi(PG_VAL(1));
		PQclear(result);
	} else
		rc = SLURM_ERROR;
	return rc;
}
