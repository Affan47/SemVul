TransactionIdLatest(TransactionId mainxid,
					int nxids, const TransactionId *xids)
{
	TransactionId result;


	result = mainxid;
	while (--nxids >= 0)
	{
		if (TransactionIdPrecedes(result, xids[nxids]))
			result = xids[nxids];
	}
	return result;
}
