xfs_mru_cache_delete(
	struct xfs_mru_cache	*mru,
	unsigned long		key)
{
	struct xfs_mru_cache_elem *elem;

	elem = xfs_mru_cache_remove(mru, key);
	if (elem)
		mru->free_func(elem);
}
