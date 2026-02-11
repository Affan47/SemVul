globus_libc_seekdir(DIR *dirp,
		    long loc)
{
    int save_errno;

    if(dirp != GLOBUS_NULL)
    {
	globus_libc_lock();

	seekdir(dirp, loc);

	save_errno = errno;

	globus_libc_unlock();
	errno = save_errno;
	return;
    }
}
