BeginStrongLockAcquire(LOCALLOCK *locallock, uint32 fasthashcode)
{
	Assert(StrongLockInProgress == NULL);
	Assert(locallock->holdsStrongLockCount == FALSE);


	SpinLockAcquire(&FastPathStrongRelationLocks->mutex);
	FastPathStrongRelationLocks->count[fasthashcode]++;
	locallock->holdsStrongLockCount = TRUE;
	StrongLockInProgress = locallock;
	SpinLockRelease(&FastPathStrongRelationLocks->mutex);
}
