GetAvgFSMRequestSize(RelFileNode *rel)
{
	Size		result;
	FSMRelation *fsmrel;

	LWLockAcquire(FreeSpaceLock, LW_EXCLUSIVE);
	fsmrel = lookup_fsm_rel(rel);
	if (fsmrel)
		result = fsmrel->avgRequest;
	else
		result = INITIAL_AVERAGE;
	LWLockRelease(FreeSpaceLock);
	return result;
}
