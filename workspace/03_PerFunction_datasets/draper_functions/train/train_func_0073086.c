jffs2_do_clear_inode(struct jffs2_sb_info *c, struct jffs2_inode_info *f)
{
	struct jffs2_full_dirent *fd, *fds;
	int deleted;

	jffs2_xattr_delete_inode(c, f->inocache);
	mutex_lock(&f->sem);
	deleted = f->inocache && !f->inocache->pino_nlink;

	if (f->inocache && f->inocache->state != INO_STATE_CHECKING)
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_CLEARING);

	if (f->metadata) {
		if (deleted)
			jffs2_mark_node_obsolete(c, f->metadata->raw);
		jffs2_free_full_dnode(f->metadata);
	}

	jffs2_kill_fragtree(&f->fragtree, deleted?c:NULL);

	if (f->target) {
		kfree(f->target);
		f->target = NULL;
	}

	fds = f->dents;
	while(fds) {
		fd = fds;
		fds = fd->next;
		jffs2_free_full_dirent(fd);
	}

	if (f->inocache && f->inocache->state != INO_STATE_CHECKING) {
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		if (f->inocache->nodes == (void *)f->inocache)
			jffs2_del_ino_cache(c, f->inocache);
	}

	mutex_unlock(&f->sem);
}
