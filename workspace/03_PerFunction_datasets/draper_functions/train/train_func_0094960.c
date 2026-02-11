_bt_check_unique(Relation rel, IndexTuple itup, Relation heapRel,
				 Buffer buf, OffsetNumber offset, ScanKey itup_scankey)
{
	TupleDesc	itupdesc = RelationGetDescr(rel);
	int			natts = rel->rd_rel->relnatts;
	SnapshotData SnapshotDirty;
	OffsetNumber maxoff;
	Page		page;
	BTPageOpaque opaque;
	Buffer		nbuf = InvalidBuffer;

	InitDirtySnapshot(SnapshotDirty);

	page = BufferGetPage(buf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	maxoff = PageGetMaxOffsetNumber(page);


	for (;;)
	{
		ItemId		curitemid;
		IndexTuple	curitup;
		BlockNumber nblkno;


		if (offset <= maxoff)
		{
			curitemid = PageGetItemId(page, offset);


			if (!ItemIdIsDead(curitemid))
			{
				ItemPointerData htid;
				bool		all_dead;


				if (!_bt_isequal(itupdesc, page, offset, natts, itup_scankey))
					break;


				curitup = (IndexTuple) PageGetItem(page, curitemid);
				htid = curitup->t_tid;


				if (heap_hot_search(&htid, heapRel, &SnapshotDirty, &all_dead))
				{

					TransactionId xwait =
					(TransactionIdIsValid(SnapshotDirty.xmin)) ?
					SnapshotDirty.xmin : SnapshotDirty.xmax;


					if (TransactionIdIsValid(xwait))
					{
						if (nbuf != InvalidBuffer)
							_bt_relbuf(rel, nbuf);

						return xwait;
					}


					htid = itup->t_tid;
					if (heap_hot_search(&htid, heapRel, SnapshotSelf, NULL))
					{

					}
					else
					{


						break;
					}

					ereport(ERROR,
							(errcode(ERRCODE_UNIQUE_VIOLATION),
							 errmsg("duplicate key value violates unique constraint \"%s\"",
									RelationGetRelationName(rel))));
				}
				else if (all_dead)
				{


					ItemIdMarkDead(curitemid);
					opaque->btpo_flags |= BTP_HAS_GARBAGE;

					if (nbuf != InvalidBuffer)
						SetBufferCommitInfoNeedsSave(nbuf);
					else
						SetBufferCommitInfoNeedsSave(buf);
				}
			}
		}


		if (offset < maxoff)
			offset = OffsetNumberNext(offset);
		else
		{

			if (P_RIGHTMOST(opaque))
				break;
			if (!_bt_isequal(itupdesc, page, P_HIKEY,
							 natts, itup_scankey))
				break;

			for (;;)
			{
				nblkno = opaque->btpo_next;
				nbuf = _bt_relandgetbuf(rel, nbuf, nblkno, BT_READ);
				page = BufferGetPage(nbuf);
				opaque = (BTPageOpaque) PageGetSpecialPointer(page);
				if (!P_IGNORE(opaque))
					break;
				if (P_RIGHTMOST(opaque))
					elog(ERROR, "fell off the end of index \"%s\"",
						 RelationGetRelationName(rel));
			}
			maxoff = PageGetMaxOffsetNumber(page);
			offset = P_FIRSTDATAKEY(opaque);
		}
	}

	if (nbuf != InvalidBuffer)
		_bt_relbuf(rel, nbuf);

	return InvalidTransactionId;
}
