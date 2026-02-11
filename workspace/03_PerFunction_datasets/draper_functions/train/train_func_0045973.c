_bt_doinsert(Relation rel, IndexTuple itup,
			 bool index_is_unique, Relation heapRel)
{
	int			natts = rel->rd_rel->relnatts;
	ScanKey		itup_scankey;
	BTStack		stack;
	Buffer		buf;
	OffsetNumber offset;


	itup_scankey = _bt_mkscankey(rel, itup);

top:

	stack = _bt_search(rel, natts, itup_scankey, false, &buf, BT_WRITE);

	offset = InvalidOffsetNumber;


	LockBuffer(buf, BUFFER_LOCK_UNLOCK);
	LockBuffer(buf, BT_WRITE);


	buf = _bt_moveright(rel, buf, natts, itup_scankey, false, BT_WRITE);


	if (index_is_unique)
	{
		TransactionId xwait;

		offset = _bt_binsrch(rel, buf, natts, itup_scankey, false);
		xwait = _bt_check_unique(rel, itup, heapRel, buf, offset, itup_scankey);

		if (TransactionIdIsValid(xwait))
		{

			_bt_relbuf(rel, buf);
			XactLockTableWait(xwait);

			_bt_freestack(stack);
			goto top;
		}
	}


	_bt_findinsertloc(rel, &buf, &offset, natts, itup_scankey, itup);
	_bt_insertonpg(rel, buf, stack, itup, offset, false);


	_bt_freestack(stack);
	_bt_freeskey(itup_scankey);
}
