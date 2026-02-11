LockReassignCurrentOwner(void)
{
	ResourceOwner parent = ResourceOwnerGetParent(CurrentResourceOwner);
	HASH_SEQ_STATUS status;
	LOCALLOCK  *locallock;
	LOCALLOCKOWNER *lockOwners;

	Assert(parent != NULL);

	hash_seq_init(&status, LockMethodLocalHash);

	while ((locallock = (LOCALLOCK *) hash_seq_search(&status)) != NULL)
	{
		int			i;
		int			ic = -1;
		int			ip = -1;


		if (!LockMethods[LOCALLOCK_LOCKMETHOD(*locallock)]->transactional)
			continue;


		lockOwners = locallock->lockOwners;
		for (i = locallock->numLockOwners - 1; i >= 0; i--)
		{
			if (lockOwners[i].owner == CurrentResourceOwner)
				ic = i;
			else if (lockOwners[i].owner == parent)
				ip = i;
		}

		if (ic < 0)
			continue;

		if (ip < 0)
		{

			lockOwners[ic].owner = parent;
		}
		else
		{

			lockOwners[ip].nLocks += lockOwners[ic].nLocks;

			locallock->numLockOwners--;
			if (ic < locallock->numLockOwners)
				lockOwners[ic] = lockOwners[locallock->numLockOwners];
		}
	}
}
