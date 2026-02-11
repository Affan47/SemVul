HeapTupleSatisfiesToast(HeapTupleHeader tuple, Buffer buffer)
{
	if (!(tuple->t_infomask & HEAP_XMIN_COMMITTED))
	{
		if (tuple->t_infomask & HEAP_XMIN_INVALID)
			return false;

		if (tuple->t_infomask & HEAP_MOVED_OFF)
		{
			TransactionId xvac = HeapTupleHeaderGetXvac(tuple);

			if (TransactionIdIsCurrentTransactionId(xvac))
				return false;
			if (!TransactionIdIsInProgress(xvac))
			{
				if (TransactionIdDidCommit(xvac))
				{
					tuple->t_infomask |= HEAP_XMIN_INVALID;
					SetBufferCommitInfoNeedsSave(buffer);
					return false;
				}
				tuple->t_infomask |= HEAP_XMIN_COMMITTED;
				SetBufferCommitInfoNeedsSave(buffer);
			}
		}
		else if (tuple->t_infomask & HEAP_MOVED_IN)
		{
			TransactionId xvac = HeapTupleHeaderGetXvac(tuple);

			if (!TransactionIdIsCurrentTransactionId(xvac))
			{
				if (TransactionIdIsInProgress(xvac))
					return false;
				if (TransactionIdDidCommit(xvac))
				{
					tuple->t_infomask |= HEAP_XMIN_COMMITTED;
					SetBufferCommitInfoNeedsSave(buffer);
				}
				else
				{
					tuple->t_infomask |= HEAP_XMIN_INVALID;
					SetBufferCommitInfoNeedsSave(buffer);
					return false;
				}
			}
		}
	}


	return true;
}
