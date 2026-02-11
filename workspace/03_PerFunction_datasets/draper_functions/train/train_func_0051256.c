InitAuxiliaryProcess(void)
{
	PGPROC	   *auxproc;
	int			proctype;
	int			i;


	if (ProcGlobal == NULL || AuxiliaryProcs == NULL)
		elog(PANIC, "proc header uninitialized");

	if (MyProc != NULL)
		elog(ERROR, "you already exist");


	SpinLockAcquire(ProcStructLock);

	set_spins_per_delay(ProcGlobal->spins_per_delay);


	for (proctype = 0; proctype < NUM_AUXILIARY_PROCS; proctype++)
	{
		auxproc = &AuxiliaryProcs[proctype];
		if (auxproc->pid == 0)
			break;
	}
	if (proctype >= NUM_AUXILIARY_PROCS)
	{
		SpinLockRelease(ProcStructLock);
		elog(FATAL, "all AuxiliaryProcs are in use");
	}


	((volatile PGPROC *) auxproc)->pid = MyProcPid;

	MyProc = auxproc;

	SpinLockRelease(ProcStructLock);


	SHMQueueElemInit(&(MyProc->links));
	MyProc->waitStatus = STATUS_OK;
	MyProc->lxid = InvalidLocalTransactionId;
	MyProc->xid = InvalidTransactionId;
	MyProc->xmin = InvalidTransactionId;
	MyProc->backendId = InvalidBackendId;
	MyProc->databaseId = InvalidOid;
	MyProc->roleId = InvalidOid;
	MyProc->inCommit = false;
	MyProc->vacuumFlags = 0;
	MyProc->lwWaiting = false;
	MyProc->lwExclusive = false;
	MyProc->lwWaitLink = NULL;
	MyProc->waitLock = NULL;
	MyProc->waitProcLock = NULL;
	for (i = 0; i < NUM_LOCK_PARTITIONS; i++)
		SHMQueueInit(&(MyProc->myProcLocks[i]));


	PGSemaphoreReset(&MyProc->sem);


	on_shmem_exit(AuxiliaryProcKill, Int32GetDatum(proctype));
}
