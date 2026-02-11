_bt_endpoint(IndexScanDesc scan, ScanDirection dir)
{
	Relation	rel = scan->indexRelation;
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	Buffer		buf;
	Page		page;
	BTPageOpaque opaque;
	OffsetNumber start;


	buf = _bt_get_endpoint(rel, 0, ScanDirectionIsBackward(dir));

	if (!BufferIsValid(buf))
	{


		PredicateLockRelation(rel, scan->xs_snapshot);
		so->currPos.buf = InvalidBuffer;
		return false;
	}

	PredicateLockPage(rel, BufferGetBlockNumber(buf), scan->xs_snapshot);
	page = BufferGetPage(buf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	Assert(P_ISLEAF(opaque));

	if (ScanDirectionIsForward(dir))
	{


		start = P_FIRSTDATAKEY(opaque);
	}
	else if (ScanDirectionIsBackward(dir))
	{
		Assert(P_RIGHTMOST(opaque));

		start = PageGetMaxOffsetNumber(page);
	}
	else
	{
		elog(ERROR, "invalid scan direction: %d", (int) dir);
		start = 0;
	}


	so->currPos.buf = buf;


	if (ScanDirectionIsForward(dir))
	{
		so->currPos.moreLeft = false;
		so->currPos.moreRight = true;
	}
	else
	{
		so->currPos.moreLeft = true;
		so->currPos.moreRight = false;
	}
	so->numKilled = 0;
	so->markItemIndex = -1;


	if (!_bt_readpage(scan, dir, start))
	{


		if (!_bt_steppage(scan, dir))
			return false;
	}


	LockBuffer(so->currPos.buf, BUFFER_LOCK_UNLOCK);


	scan->xs_ctup.t_self = so->currPos.items[so->currPos.itemIndex].heapTid;

	return true;
}
