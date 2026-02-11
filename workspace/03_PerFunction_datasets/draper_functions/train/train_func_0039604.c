RemoveScratchTarget(bool lockheld)
{
	bool		found;

	Assert(LWLockHeldByMe(SerializablePredicateLockListLock));

	if (!lockheld)
		LWLockAcquire(ScratchPartitionLock, LW_EXCLUSIVE);
	hash_search_with_hash_value(PredicateLockTargetHash,
								&ScratchTargetTag,
								ScratchTargetTagHash,
								HASH_REMOVE, &found);
	Assert(found);
	if (!lockheld)
		LWLockRelease(ScratchPartitionLock);
}
