SubTransGetParent(TransactionId xid)
{
	int			pageno = TransactionIdToPage(xid);
	int			entryno = TransactionIdToEntry(xid);
	int			slotno;
	TransactionId *ptr;
	TransactionId parent;


	Assert(TransactionIdFollowsOrEquals(xid, TransactionXmin));


	if (!TransactionIdIsNormal(xid))
		return InvalidTransactionId;


	slotno = SimpleLruReadPage_ReadOnly(SubTransCtl, pageno, xid);
	ptr = (TransactionId *) SubTransCtl->shared->page_buffer[slotno];
	ptr += entryno;

	parent = *ptr;

	LWLockRelease(SubtransControlLock);

	return parent;
}
