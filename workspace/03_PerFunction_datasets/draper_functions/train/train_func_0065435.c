_bt_delitems_vacuum(Relation rel, Buffer buf,
			OffsetNumber *itemnos, int nitems, BlockNumber lastBlockVacuumed)
{
	Page		page = BufferGetPage(buf);
	BTPageOpaque opaque;


	START_CRIT_SECTION();


	if (nitems > 0)
		PageIndexMultiDelete(page, itemnos, nitems);


	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	opaque->btpo_cycleid = 0;


	opaque->btpo_flags &= ~BTP_HAS_GARBAGE;

	MarkBufferDirty(buf);


	if (RelationNeedsWAL(rel))
	{
		XLogRecPtr	recptr;
		XLogRecData rdata[2];

		xl_btree_vacuum xlrec_vacuum;

		xlrec_vacuum.node = rel->rd_node;
		xlrec_vacuum.block = BufferGetBlockNumber(buf);

		xlrec_vacuum.lastBlockVacuumed = lastBlockVacuumed;
		rdata[0].data = (char *) &xlrec_vacuum;
		rdata[0].len = SizeOfBtreeVacuum;
		rdata[0].buffer = InvalidBuffer;
		rdata[0].next = &(rdata[1]);


		if (nitems > 0)
		{
			rdata[1].data = (char *) itemnos;
			rdata[1].len = nitems * sizeof(OffsetNumber);
		}
		else
		{
			rdata[1].data = NULL;
			rdata[1].len = 0;
		}
		rdata[1].buffer = buf;
		rdata[1].buffer_std = true;
		rdata[1].next = NULL;

		recptr = XLogInsert(RM_BTREE_ID, XLOG_BTREE_VACUUM, rdata);

		PageSetLSN(page, recptr);
		PageSetTLI(page, ThisTimeLineID);
	}

	END_CRIT_SECTION();
}
