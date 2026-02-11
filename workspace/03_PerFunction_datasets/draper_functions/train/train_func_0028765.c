_xfs_mru_cache_list_insert(
	struct xfs_mru_cache	*mru,
	struct xfs_mru_cache_elem *elem)
{
	unsigned int		grp = 0;
	unsigned long		now = jiffies;


	if (!_xfs_mru_cache_migrate(mru, now)) {
		mru->time_zero = now;
		if (!mru->queued) {
			mru->queued = 1;
			queue_delayed_work(xfs_mru_reap_wq, &mru->work,
			                   mru->grp_count * mru->grp_time);
		}
	} else {
		grp = (now - mru->time_zero) / mru->grp_time;
		grp = (mru->lru_grp + grp) % mru->grp_count;
	}


	list_add_tail(&elem->list_node, mru->lists + grp);
}
