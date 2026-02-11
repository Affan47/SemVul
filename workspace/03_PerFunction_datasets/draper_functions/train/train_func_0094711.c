PostPrepare_smgr(void)
{
	PendingRelDelete *pending;
	PendingRelDelete *next;

	for (pending = pendingDeletes; pending != NULL; pending = next)
	{
		next = pending->next;
		pendingDeletes = next;

		pfree(pending);
	}
}
