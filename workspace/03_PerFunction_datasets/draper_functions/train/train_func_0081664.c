ovdb_releaselock(void)
{
    bool r;
    if(lockfd == -1)
	return true;
    r = inn_lock_file(lockfd, INN_LOCK_UNLOCK, false);
    close(lockfd);
    lockfd = -1;
    return r;
}
