extractPageInfo(XLogReaderState *record)
{
	int			block_id;
	RmgrId		rmid = XLogRecGetRmid(record);
	uint8		info = XLogRecGetInfo(record);
	uint8		rminfo = info & ~XLR_INFO_MASK;


	if (rmid == RM_DBASE_ID && rminfo == XLOG_DBASE_CREATE)
	{


	}
	else if (rmid == RM_DBASE_ID && rminfo == XLOG_DBASE_DROP)
	{


	}
	else if (rmid == RM_SMGR_ID && rminfo == XLOG_SMGR_CREATE)
	{


	}
	else if (rmid == RM_SMGR_ID && rminfo == XLOG_SMGR_TRUNCATE)
	{


	}
	else if (info & XLR_SPECIAL_REL_UPDATE)
	{


		pg_fatal("WAL record modifies a relation, but record type is not recognized\n"
				 "lsn: %X/%X, rmgr: %s, info: %02X\n",
		  (uint32) (record->ReadRecPtr >> 32), (uint32) (record->ReadRecPtr),
				 RmgrNames[rmid], info);
	}

	for (block_id = 0; block_id <= record->max_block_id; block_id++)
	{
		RelFileNode rnode;
		ForkNumber	forknum;
		BlockNumber blkno;

		if (!XLogRecGetBlockTag(record, block_id, &rnode, &forknum, &blkno))
			continue;


		if (forknum != MAIN_FORKNUM)
			continue;

		process_block_change(forknum, rnode, blkno);
	}
}
