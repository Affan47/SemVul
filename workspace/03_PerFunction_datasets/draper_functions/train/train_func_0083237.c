move_expired_inodes(struct list_head *delaying_queue,
			       struct list_head *dispatch_queue,
			       int flags,
			       struct wb_writeback_work *work)
{
	unsigned long *older_than_this = NULL;
	unsigned long expire_time;
	LIST_HEAD(tmp);
	struct list_head *pos, *node;
	struct super_block *sb = NULL;
	struct inode *inode;
	int do_sb_sort = 0;
	int moved = 0;

	if ((flags & EXPIRE_DIRTY_ATIME) == 0)
		older_than_this = work->older_than_this;
	else if (!work->for_sync) {
		expire_time = jiffies - (dirtytime_expire_interval * HZ);
		older_than_this = &expire_time;
	}
	while (!list_empty(delaying_queue)) {
		inode = wb_inode(delaying_queue->prev);
		if (older_than_this &&
		    inode_dirtied_after(inode, *older_than_this))
			break;
		list_move(&inode->i_io_list, &tmp);
		moved++;
		if (flags & EXPIRE_DIRTY_ATIME)
			set_bit(__I_DIRTY_TIME_EXPIRED, &inode->i_state);
		if (sb_is_blkdev_sb(inode->i_sb))
			continue;
		if (sb && sb != inode->i_sb)
			do_sb_sort = 1;
		sb = inode->i_sb;
	}


	if (!do_sb_sort) {
		list_splice(&tmp, dispatch_queue);
		goto out;
	}


	while (!list_empty(&tmp)) {
		sb = wb_inode(tmp.prev)->i_sb;
		list_for_each_prev_safe(pos, node, &tmp) {
			inode = wb_inode(pos);
			if (inode->i_sb == sb)
				list_move(&inode->i_io_list, dispatch_queue);
		}
	}
out:
	return moved;
}
