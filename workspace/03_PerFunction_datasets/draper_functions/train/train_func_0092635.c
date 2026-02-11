list_splice_with_locker(Locker *locker, List *list, ssize_t index, ssize_t range, list_copy_t *copy)
{
	List *ret;
	int err;

	if (!list)
		return set_errnull(EINVAL);

	if ((err = list_wrlock(list)))
		return set_errnull(err);

	ret = list_splice_with_locker_unlocked(locker, list, index, range, copy);

	if ((err = list_unlock(list)))
	{
		list_release(ret);
		return set_errnull(err);
	}

	return ret;
}
