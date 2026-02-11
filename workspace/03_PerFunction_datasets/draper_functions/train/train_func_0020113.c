LWLockRegisterTranche(int tranche_id, LWLockTranche *tranche)
{
	Assert(LWLockTrancheArray != NULL);

	if (tranche_id >= LWLockTranchesAllocated)
	{
		int			i = LWLockTranchesAllocated;

		while (i <= tranche_id)
			i *= 2;

		LWLockTrancheArray = (LWLockTranche **)
			repalloc(LWLockTrancheArray,
					 i * sizeof(LWLockTranche *));
		LWLockTranchesAllocated = i;
	}

	LWLockTrancheArray[tranche_id] = tranche;
}
