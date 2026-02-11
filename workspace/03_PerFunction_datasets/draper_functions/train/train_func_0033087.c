ReorderBufferCopySnap(ReorderBuffer *rb, Snapshot orig_snap,
					  ReorderBufferTXN *txn, CommandId cid)
{
	Snapshot	snap;
	dlist_iter	iter;
	int			i = 0;
	Size		size;

	size = sizeof(SnapshotData) +
		sizeof(TransactionId) * orig_snap->xcnt +
		sizeof(TransactionId) * (txn->nsubtxns + 1);

	snap = MemoryContextAllocZero(rb->context, size);
	memcpy(snap, orig_snap, sizeof(SnapshotData));

	snap->copied = true;
	snap->active_count = 1;
	snap->regd_count = 0;
	snap->xip = (TransactionId *) (snap + 1);

	memcpy(snap->xip, orig_snap->xip, sizeof(TransactionId) * snap->xcnt);


	snap->subxip = snap->xip + snap->xcnt;
	snap->subxip[i++] = txn->xid;


	snap->subxcnt = 1;

	dlist_foreach(iter, &txn->subtxns)
	{
		ReorderBufferTXN *sub_txn;

		sub_txn = dlist_container(ReorderBufferTXN, node, iter.cur);
		snap->subxip[i++] = sub_txn->xid;
		snap->subxcnt++;
	}


	qsort(snap->subxip, snap->subxcnt, sizeof(TransactionId), xidComparator);


	snap->curcid = cid;

	return snap;
}
