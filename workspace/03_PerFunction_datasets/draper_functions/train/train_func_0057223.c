remove_lock_files (struct lock *lock, bool free_repository)
{
    TRACE (TRACE_FLOW, "remove_lock_files (%s)", lock->repository);


    if (lock->file1)
    {
	char *tmp = lock->file1;
	lock->file1 = NULL;
	if (CVS_UNLINK (tmp) < 0 && ! existence_error (errno))
	    error (0, errno, "failed to remove lock %s", tmp);
	free (tmp);
    }
#ifdef LOCK_COMPATIBILITY
    if (lock->file2)
    {
	char *tmp = lock->file2;
	lock->file2 = NULL;
	if (CVS_UNLINK (tmp) < 0 && ! existence_error (errno))
	    error (0, errno, "failed to remove lock %s", tmp);
	free (tmp);
    }
#endif

    clear_lock (lock);


    if (free_repository)
    {
	SIG_beginCrSect ();
	if (lock->free_repository)
	{
	    free ((char *)lock->repository);
	    lock->free_repository = false;
	}
	lock->repository = NULL;
	SIG_endCrSect ();
    }
}
