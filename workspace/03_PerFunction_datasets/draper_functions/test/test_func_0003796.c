__lv_on_nontxn_update(lvh, lsnp, txnid, logtype, fileid)
	DB_LOG_VRFY_INFO *lvh;
	const DB_LSN *lsnp;
	u_int32_t txnid, logtype;
	int32_t fileid;
{
	lvh->lrtypes[logtype]++;
	COMPQUIET(txnid, 0);
	if (fileid != INVAL_DBREGID) {
		lvh->non_txnup_cnt++;
		__db_msg(lvh->dbenv->env, DB_STR_A("2565",
		    "[%lu][%lu] Non-transactional update, "
		    "log type: %u, fileid: %d.", "%lu %lu %u %d"),
		    (u_long)lsnp->file, (u_long)lsnp->offset, logtype, fileid);
	}

	return (0);
}
