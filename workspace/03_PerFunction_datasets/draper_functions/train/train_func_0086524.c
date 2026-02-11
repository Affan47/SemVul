__os_unmapfile(env, addr, len)
	ENV *env;
	void *addr;
	size_t len;
{
	DB_ENV *dbenv;
	int ret;


	DB_ASSERT(env, env != NULL && env->dbenv != NULL);
	dbenv = env->dbenv;

	if (FLD_ISSET(dbenv->verbose, DB_VERB_FILEOPS | DB_VERB_FILEOPS_ALL))
		__db_msg(env, DB_STR("0124", "fileops: munmap"));


	if (DB_GLOBAL(j_file_unmap) != NULL)
		return (DB_GLOBAL(j_file_unmap)(dbenv, addr));

#ifdef HAVE_MMAP
#ifdef HAVE_MUNLOCK
	if (F_ISSET(env, ENV_LOCKDOWN))
		RETRY_CHK((munlock(addr, len)), ret);


#else
	COMPQUIET(env, NULL);
#endif
	RETRY_CHK((munmap(addr, len)), ret);
	ret = __os_posix_err(ret);
#else
	COMPQUIET(env, NULL);
	ret = EINVAL;
#endif
	return (ret);
}
