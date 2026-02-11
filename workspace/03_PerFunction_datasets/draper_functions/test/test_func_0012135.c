CDB___os_r_sysdetach(dbenv, infop, destroy)
	DB_ENV *dbenv;
	REGINFO *infop;
	int destroy;
{
	REGION *rp;
	int segid;

	rp = infop->rp;

	if (F_ISSET(dbenv, DB_ENV_SYSTEM_MEM)) {
#ifdef HAVE_SHMGET


		segid = rp->segid;
		if (destroy)
			rp->segid = INVALID_REGION_SEGID;

		if (shmdt(infop->addr) != 0)
			return (CDB___os_get_errno());

		if (destroy)
			if (shmctl(segid, IPC_RMID, NULL) != 0)
				return (CDB___os_get_errno());

		return (0);
#else
		return (EINVAL);
#endif
	}

#ifdef HAVE_MMAP
#ifdef HAVE_MUNLOCK
	if (F_ISSET(dbenv, DB_ENV_LOCKDOWN))
		(void)munlock(infop->addr, rp->size);
#endif
	if (munmap(infop->addr, rp->size) != 0)
		return (CDB___os_get_errno());

	if (destroy && CDB___os_unlink(infop->name) != 0)
		return (CDB___os_get_errno());
	return (0);
#else
	return (EINVAL);
#endif
}
