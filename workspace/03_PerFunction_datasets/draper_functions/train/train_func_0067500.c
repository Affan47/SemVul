btbuildempty(PG_FUNCTION_ARGS)
{
	Relation	index = (Relation) PG_GETARG_POINTER(0);
	Page		metapage;


	metapage = (Page) palloc(BLCKSZ);
	_bt_initmetapage(metapage, P_NONE, 0);


	PageSetChecksumInplace(metapage, BTREE_METAPAGE);
	smgrwrite(index->rd_smgr, INIT_FORKNUM, BTREE_METAPAGE,
			  (char *) metapage, true);
	if (XLogIsNeeded())
		log_newpage(&index->rd_smgr->smgr_rnode.node, INIT_FORKNUM,
					BTREE_METAPAGE, metapage, false);


	smgrimmedsync(index->rd_smgr, INIT_FORKNUM);

	PG_RETURN_VOID();
}
