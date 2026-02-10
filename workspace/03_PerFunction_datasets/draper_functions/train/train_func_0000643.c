PredicateLockTuple(Relation relation, HeapTuple tuple, Snapshot snapshot)
{
	PREDICATELOCKTARGETTAG tag;
	ItemPointer tid;
	TransactionId targetxmin;

	if (!SerializationNeededForRead(relation, snapshot))
		return;


	if (relation->rd_index == NULL)
	{
		TransactionId myxid;

		targetxmin = HeapTupleHeaderGetXmin(tuple->t_data);

		myxid = GetTopTransactionIdIfAny();
		if (TransactionIdIsValid(myxid))
		{
			if (TransactionIdFollowsOrEquals(targetxmin, TransactionXmin))
			{
				TransactionId xid = SubTransGetTopmostTransaction(targetxmin);

				if (TransactionIdEquals(xid, myxid))
				{

					return;
				}
			}
		}
	}


	SET_PREDICATELOCKTARGETTAG_RELATION(tag,
										relation->rd_node.dbNode,
										relation->rd_id);
	if (PredicateLockExists(&tag))
		return;

	tid = &(tuple->t_self);
	SET_PREDICATELOCKTARGETTAG_TUPLE(tag,
									 relation->rd_node.dbNode,
									 relation->rd_id,
									 ItemPointerGetBlockNumber(tid),
									 ItemPointerGetOffsetNumber(tid));
	PredicateLockAcquire(&tag);
}
