vacuum_set_xid_limits(int freeze_min_age, bool sharedRel,
					  TransactionId *oldestXmin,
					  TransactionId *freezeLimit)
{
	int			freezemin;
	TransactionId limit;
	TransactionId safeLimit;


	*oldestXmin = GetOldestXmin(sharedRel, true);

	Assert(TransactionIdIsNormal(*oldestXmin));


	freezemin = freeze_min_age;
	if (freezemin < 0)
		freezemin = vacuum_freeze_min_age;
	freezemin = Min(freezemin, autovacuum_freeze_max_age / 2);
	Assert(freezemin >= 0);


	limit = *oldestXmin - freezemin;
	if (!TransactionIdIsNormal(limit))
		limit = FirstNormalTransactionId;


	safeLimit = ReadNewTransactionId() - autovacuum_freeze_max_age;
	if (!TransactionIdIsNormal(safeLimit))
		safeLimit = FirstNormalTransactionId;

	if (TransactionIdPrecedes(limit, safeLimit))
	{
		ereport(WARNING,
				(errmsg("oldest xmin is far in the past"),
				 errhint("Close open transactions soon to avoid wraparound problems.")));
		limit = *oldestXmin;
	}

	*freezeLimit = limit;
}
