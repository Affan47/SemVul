remote_lock_held(const char *vol, int *exclusive)
{
	int mode = LCK_NULL;

	if (!locking_is_clustered())
		return 0;

	if (!_locking.query_resource)
		return -1;


	if (!_locking.query_resource(vol, &mode)) {
		stack;
		return 1;
	}

	if (exclusive)
		*exclusive = (mode == LCK_EXCL);

	return mode == LCK_NULL ? 0 : 1;
}
