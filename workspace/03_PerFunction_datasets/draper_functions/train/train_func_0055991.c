TransactionIdGetCommitLSN(TransactionId xid)
{
	XLogRecPtr	result;


	if (TransactionIdEquals(xid, cachedFetchXid))
		return cachedCommitLSN;


	if (!TransactionIdIsNormal(xid))
		return InvalidXLogRecPtr;


	(void) TransactionIdGetStatus(xid, &result);

	return result;
}
