CDB___os_map(dbenv, path, fhp, len, is_region, is_rdonly, addrp)
	DB_ENV *dbenv;
	char *path;
	DB_FH *fhp;
	int is_region, is_rdonly;
	size_t len;
	void **addrp;
{
	void *p;
	int flags, prot;


	if (CDB___db_jump.j_map != NULL)
		return (CDB___db_jump.j_map
		    (path, len, is_region, is_rdonly, addrp));


	flags = is_rdonly ? MAP_PRIVATE : MAP_SHARED;

#ifdef MAP_FILE


	flags |= MAP_FILE;
#endif


#ifdef MAP_HASSEMAPHORE
	if (is_region && !is_rdonly)
		flags |= MAP_HASSEMAPHORE;
#else
	COMPQUIET(is_region, 0);
#endif

	prot = PROT_READ | (is_rdonly ? 0 : PROT_WRITE);


#ifdef VMS
	if (CDB___os_fsync(fhp) == -1)
		return(CDB___os_get_errno());
#endif


#ifndef MAP_FAILED
#define	MAP_FAILED	-1
#endif
	if ((p = mmap(NULL,
	    len, prot, flags, fhp->fd, (off_t)0)) == (void *)MAP_FAILED)
		return (CDB___os_get_errno());

#ifdef HAVE_MLOCK


	if (F_ISSET(dbenv, DB_ENV_LOCKDOWN) && mlock(p, len) != 0) {
		(void)munmap(p, len);
		return (CDB___os_get_errno());
	}
#else
	COMPQUIET(dbenv, NULL);
#endif

	*addrp = p;
	return (0);
}
