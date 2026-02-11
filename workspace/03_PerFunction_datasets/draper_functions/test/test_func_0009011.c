DeleteChildTargetLocks(const PREDICATELOCKTARGETTAG *newtargettag)
{
	SERIALIZABLEXACT *sxact;
	PREDICATELOCK *predlock;

	LWLockAcquire(SerializablePredicateLockListLock, LW_SHARED);
	sxact = MySerializableXact;
	predlock = (PREDICATELOCK *)
		SHMQueueNext(&(sxact->predicateLocks),
					 &(sxact->predicateLocks),
					 offsetof(PREDICATELOCK, xactLink));
	while (predlock)
	{
		SHM_QUEUE  *predlocksxactlink;
		PREDICATELOCK *nextpredlock;
		PREDICATELOCKTAG oldlocktag;
		PREDICATELOCKTARGET *oldtarget;
		PREDICATELOCKTARGETTAG oldtargettag;

		predlocksxactlink = &(predlock->xactLink);
		nextpredlock = (PREDICATELOCK *)
			SHMQueueNext(&(sxact->predicateLocks),
						 predlocksxactlink,
						 offsetof(PREDICATELOCK, xactLink));

		oldlocktag = predlock->tag;
		Assert(oldlocktag.myXact == sxact);
		oldtarget = oldlocktag.myTarget;
		oldtargettag = oldtarget->tag;

		if (TargetTagIsCoveredBy(oldtargettag, *newtargettag))
		{
			uint32		oldtargettaghash;
			LWLock	   *partitionLock;
			PREDICATELOCK *rmpredlock PG_USED_FOR_ASSERTS_ONLY;

			oldtargettaghash = PredicateLockTargetTagHashCode(&oldtargettag);
			partitionLock = PredicateLockHashPartitionLock(oldtargettaghash);

			LWLockAcquire(partitionLock, LW_EXCLUSIVE);

			SHMQueueDelete(predlocksxactlink);
			SHMQueueDelete(&(predlock->targetLink));
			rmpredlock = hash_search_with_hash_value
				(PredicateLockHash,
				 &oldlocktag,
				 PredicateLockHashCodeFromTargetHashCode(&oldlocktag,
														 oldtargettaghash),
				 HASH_REMOVE, NULL);
			Assert(rmpredlock == predlock);

			RemoveTargetIfNoLongerUsed(oldtarget, oldtargettaghash);

			LWLockRelease(partitionLock);

			DecrementParentLocks(&oldtargettag);
		}

		predlock = nextpredlock;
	}
	LWLockRelease(SerializablePredicateLockListLock);
}
