str_split_with_locker(Locker *locker, const String *str, const char *delim)
{
	List *ret;
	int err;

	if (!str || !delim)
		return set_errnull(EINVAL);

	if ((err = str_rdlock(str)))
		return set_errnull(err);

	ret = str_split_with_locker_unlocked(locker, str, delim);

	if ((err = str_unlock(str)))
	{
		list_release(ret);
		return set_errnull(err);
	}

	return ret;
}
