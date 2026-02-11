GetIsActive(const PROC * proc)
{
	if (proc->isActive)
		return TRUE;

	if (!useThreads && !showThreads)
		return FALSE;

	if (proc->isThread || (proc->threadCount == 1))
		return FALSE;

	for (proc = proc->nextThread; proc; proc = proc->nextThread)
	{
		if (proc->isActive)
			return TRUE;
	}

	return FALSE;
}
