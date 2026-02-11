GetCurrentVirtualXIDs(TransactionId limitXmin, bool allDbs, int excludeVacuum)
{
	VirtualTransactionId *vxids;
	ProcArrayStruct *arrayP = procArray;
	int			count = 0;
	int			index;


	vxids = (VirtualTransactionId *)
		palloc(sizeof(VirtualTransactionId) * (arrayP->maxProcs + 1));

	LWLockAcquire(ProcArrayLock, LW_SHARED);

	for (index = 0; index < arrayP->numProcs; index++)
	{
		volatile PGPROC *proc = arrayP->procs[index];

		if (proc == MyProc)
			continue;

		if (excludeVacuum & proc->vacuumFlags)
			continue;

		if (allDbs || proc->databaseId == MyDatabaseId)
		{

			TransactionId pxmin = proc->xmin;


			if (!TransactionIdIsValid(limitXmin) ||
				TransactionIdPrecedes(pxmin, limitXmin))
			{
				VirtualTransactionId vxid;

				GET_VXID_FROM_PGPROC(vxid, *proc);
				if (VirtualTransactionIdIsValid(vxid))
					vxids[count++] = vxid;
			}
		}
	}

	LWLockRelease(ProcArrayLock);


	vxids[count].backendId = InvalidBackendId;
	vxids[count].localTransactionId = InvalidLocalTransactionId;

	return vxids;
}
