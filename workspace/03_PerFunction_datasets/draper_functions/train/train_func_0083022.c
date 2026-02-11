mdb_dcmp(MDB_txn *txn, MDB_dbi dbi, const MDB_val *a, const MDB_val *b)
{
	if (txn->mt_dbxs[dbi].md_dcmp)
		return txn->mt_dbxs[dbi].md_dcmp(a, b);
	else
		return EINVAL;
}
