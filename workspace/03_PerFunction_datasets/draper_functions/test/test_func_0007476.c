fsnotify_detach_mark(struct fsnotify_mark *mark)
{
	struct inode *inode = NULL;
	struct fsnotify_group *group = mark->group;

	BUG_ON(!mutex_is_locked(&group->mark_mutex));

	spin_lock(&mark->lock);


	if (!(mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED)) {
		spin_unlock(&mark->lock);
		return;
	}

	mark->flags &= ~FSNOTIFY_MARK_FLAG_ATTACHED;

	if (mark->flags & FSNOTIFY_MARK_FLAG_INODE) {
		inode = mark->inode;
		fsnotify_destroy_inode_mark(mark);
	} else if (mark->flags & FSNOTIFY_MARK_FLAG_VFSMOUNT)
		fsnotify_destroy_vfsmount_mark(mark);
	else
		BUG();


	list_del_init(&mark->g_list);

	spin_unlock(&mark->lock);

	if (inode && (mark->flags & FSNOTIFY_MARK_FLAG_OBJECT_PINNED))
		iput(inode);

	atomic_dec(&group->num_marks);
}
