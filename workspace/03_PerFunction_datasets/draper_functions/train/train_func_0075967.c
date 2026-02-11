_bt_findinsertloc(Relation rel,
				  Buffer *bufptr,
				  OffsetNumber *offsetptr,
				  int keysz,
				  ScanKey scankey,
				  IndexTuple newtup)
{
	Buffer		buf = *bufptr;
	Page		page = BufferGetPage(buf);
	Size		itemsz;
	BTPageOpaque lpageop;
	bool		movedright,
				vacuumed;
	OffsetNumber newitemoff;
	OffsetNumber firstlegaloff = *offsetptr;

	lpageop = (BTPageOpaque) PageGetSpecialPointer(page);

	itemsz = IndexTupleDSize(*newtup);
	itemsz = MAXALIGN(itemsz);


	if (itemsz > BTMaxItemSize(page))
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("index row size %lu exceeds btree maximum, %lu",
						(unsigned long) itemsz,
						(unsigned long) BTMaxItemSize(page)),
		errhint("Values larger than 1/3 of a buffer page cannot be indexed.\n"
				"Consider a function index of an MD5 hash of the value, "
				"or use full text indexing.")));


	movedright = false;
	vacuumed = false;
	while (PageGetFreeSpace(page) < itemsz)
	{
		Buffer		rbuf;


		if (P_ISLEAF(lpageop) && P_HAS_GARBAGE(lpageop))
		{
			_bt_vacuum_one_page(rel, buf);


			vacuumed = true;

			if (PageGetFreeSpace(page) >= itemsz)
				break;
		}


		if (P_RIGHTMOST(lpageop) ||
			_bt_compare(rel, keysz, scankey, page, P_HIKEY) != 0 ||
			random() <= (MAX_RANDOM_VALUE / 100))
			break;


		rbuf = InvalidBuffer;

		for (;;)
		{
			BlockNumber rblkno = lpageop->btpo_next;

			rbuf = _bt_relandgetbuf(rel, rbuf, rblkno, BT_WRITE);
			page = BufferGetPage(rbuf);
			lpageop = (BTPageOpaque) PageGetSpecialPointer(page);
			if (!P_IGNORE(lpageop))
				break;
			if (P_RIGHTMOST(lpageop))
				elog(ERROR, "fell off the end of index \"%s\"",
					 RelationGetRelationName(rel));
		}
		_bt_relbuf(rel, buf);
		buf = rbuf;
		movedright = true;
		vacuumed = false;
	}


	if (movedright)
		newitemoff = P_FIRSTDATAKEY(lpageop);
	else if (firstlegaloff != InvalidOffsetNumber && !vacuumed)
		newitemoff = firstlegaloff;
	else
		newitemoff = _bt_binsrch(rel, buf, keysz, scankey, false);

	*bufptr = buf;
	*offsetptr = newitemoff;
}
