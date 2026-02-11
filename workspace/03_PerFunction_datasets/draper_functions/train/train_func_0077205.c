RemoveTargetIfNoLongerUsed(PREDICATELOCKTARGET *target, uint32 targettaghash)
{
	PREDICATELOCKTARGET *rmtarget PG_USED_FOR_ASSERTS_ONLY;

	Assert(LWLockHeldByMe(SerializablePredicateLockListLock));


	if (!SHMQueueEmpty(&target->predicateLocks))
		return;


	rmtarget = hash_search_with_hash_value(PredicateLockTargetHash,
										   &target->tag,
										   targettaghash,
										   HASH_REMOVE, NULL);
	Assert(rmtarget == target);
}
