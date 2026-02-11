__memp_backup_open(env, mpf, dbfile, target, flags, fpp, handlep)
	ENV *env;
	DB_MPOOLFILE *mpf;
	const char *dbfile;
	const char *target;
	u_int32_t flags;
	DB_FH **fpp;
	void **handlep;
{
	DB_BACKUP *backup;
#ifndef HAVE_ATOMICFILEREAD
	MPOOLFILE *mfp;
#endif
	u_int32_t oflags;
	size_t len;
	int ret;
	char *path;

	path = NULL;
	*fpp = NULL;
	backup = env->backup_handle;
	*handlep = NULL;

	if (backup != NULL && backup->open != NULL)
		ret = backup->open(env->dbenv, dbfile, target, handlep);
	else {
		len = strlen(target) + strlen(dbfile) + 2;
		if ((ret = __os_malloc(env, len, &path)) != 0) {
			__db_err(env, ret, DB_STR_A("0703",
			    "Cannot allocate space for path: %s", "%s"),
			    target);
			goto err;
		}

		if ((ret = __os_concat_path(path, len, target, dbfile)) != 0)
			goto err;

		oflags = DB_OSO_CREATE | DB_OSO_TRUNC;
		if (LF_ISSET(DB_EXCL))
			FLD_SET(oflags, DB_OSO_EXCL);
		if (backup != NULL && F_ISSET(backup, BACKUP_WRITE_DIRECT))
			FLD_SET(oflags, DB_OSO_DIRECT);
		ret = __os_open(env, path, 0, oflags, DB_MODE_600, fpp);
	}
	if (ret != 0) {
		__db_err(env, ret, DB_STR_A("0704",
		    "Cannot open target file: %s", "%s"), path);
		goto err;
	}

#ifndef HAVE_ATOMICFILEREAD
	mfp = mpf->mfp;


	MUTEX_LOCK(env, mfp->mtx_write);
	if (mfp->backup_in_progress) {
		__db_err(env, ret, DB_STR_A("0712",
		    "%s is already in a backup", "%s"), dbfile);
		MUTEX_UNLOCK(env, mfp->mtx_write);
		goto err;
	}
	mfp->backup_in_progress = 1;
	env->dbenv->thread_id(env->dbenv, &mfp->pid, &mfp->tid);
	MUTEX_UNLOCK(env, mfp->mtx_write);
#else
	COMPQUIET(mpf, NULL);
#endif
err:	if (path != NULL)
		__os_free(env, path);
	if (ret != 0) {
		if (*fpp != NULL)
			(void)__os_closehandle(env, *fpp);
		if (backup != NULL && backup->close != NULL)
			(void)backup->close(env->dbenv, dbfile, *handlep);
	}
	return (ret);
}
