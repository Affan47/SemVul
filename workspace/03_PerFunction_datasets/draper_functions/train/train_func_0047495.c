mdb_tool_idl_flush( BackendDB *be, MDB_txn *txn )
{
	struct mdb_info *mdb = (struct mdb_info *) be->be_private;
	int rc = 0;
	unsigned int i, dbi;

	for ( i=0; i < mdb->mi_nattrs; i++ ) {
		if ( !mdb->mi_attrs[i]->ai_root ) continue;
		rc = mdb_tool_idl_flush_db( txn, mdb->mi_attrs[i] );
		tavl_free(mdb->mi_attrs[i]->ai_root, NULL);
		mdb->mi_attrs[i]->ai_root = NULL;
		if ( rc )
			break;
	}
	return rc;
}
