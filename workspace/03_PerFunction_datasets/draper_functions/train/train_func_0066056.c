hash_delete(dbp, key, flag)
	const DB *dbp;
	const DBT *key;
	u_int32_t flag;
{
	HTAB *hashp;

	hashp = (HTAB *)dbp->internal;
	if (flag) {
		hashp->local_errno = errno = EINVAL;
		return (ERROR);
	}
	if ((hashp->flags & O_ACCMODE) == O_RDONLY) {
		hashp->local_errno = errno = EPERM;
		return (ERROR);
	}

	return (hash_access(hashp, HASH_DELETE, key, NULL));
}
