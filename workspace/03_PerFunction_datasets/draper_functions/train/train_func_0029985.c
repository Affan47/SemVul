mdb_cursor_touch(MDB_cursor *mc)
{
	int rc;

	if (mc->mc_dbi > MAIN_DBI && !(*mc->mc_dbflag & DB_DIRTY)) {
		MDB_cursor mc2;
		mdb_cursor_init(&mc2, mc->mc_txn, MAIN_DBI, NULL);
		rc = mdb_page_search(&mc2, &mc->mc_dbx->md_name, 1);
		if (rc)
			 return rc;
		*mc->mc_dbflag = DB_DIRTY;
	}
	for (mc->mc_top = 0; mc->mc_top < mc->mc_snum; mc->mc_top++) {
		rc = mdb_page_touch(mc);
		if (rc)
			return rc;
	}
	mc->mc_top = mc->mc_snum-1;
	return MDB_SUCCESS;
}
