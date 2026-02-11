btrfs_try_tree_write_lock(struct extent_buffer *eb)
{
	if (atomic_read(&eb->blocking_writers) ||
	    atomic_read(&eb->blocking_readers))
		return 0;

	write_lock(&eb->lock);
	if (atomic_read(&eb->blocking_writers) ||
	    atomic_read(&eb->blocking_readers)) {
		write_unlock(&eb->lock);
		return 0;
	}
	atomic_inc(&eb->write_locks);
	atomic_inc(&eb->spinning_writers);
	eb->lock_owner = current->pid;
	return 1;
}
