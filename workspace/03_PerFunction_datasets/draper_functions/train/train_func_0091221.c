btrfs_tree_unlock(struct extent_buffer *eb)
{
	int blockers = atomic_read(&eb->blocking_writers);

	BUG_ON(blockers > 1);

	btrfs_assert_tree_locked(eb);
	eb->lock_owner = 0;
	atomic_dec(&eb->write_locks);

	if (blockers) {
		WARN_ON(atomic_read(&eb->spinning_writers));
		atomic_dec(&eb->blocking_writers);


		smp_mb();
		if (waitqueue_active(&eb->write_lock_wq))
			wake_up(&eb->write_lock_wq);
	} else {
		WARN_ON(atomic_read(&eb->spinning_writers) != 1);
		atomic_dec(&eb->spinning_writers);
		write_unlock(&eb->lock);
	}
}
