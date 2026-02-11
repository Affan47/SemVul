gfp_conn_hash_table_init(
	struct gfarm_hash_table **hashtabp, int hashtabsize)
{
	struct gfarm_hash_table *hashtab;

	hashtab = gfarm_hash_table_alloc(hashtabsize,
	    gfp_conn_hash_index, gfp_conn_hash_equal);
	if (hashtab == NULL) {
		gflog_debug(GFARM_MSG_1001081,
			"allocation of hashtable(%d) failed: %s",
			hashtabsize,
			gfarm_error_string(GFARM_ERR_NO_MEMORY));
		return (GFARM_ERR_NO_MEMORY);
	}
	*hashtabp = hashtab;
	return (GFARM_ERR_NO_ERROR);
}
