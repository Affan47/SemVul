inode_init_dir(struct inode *inode, struct inode *parent)
{
	gfarm_error_t e;
	DirEntry entry;

	e = inode_init_dir_internal(inode);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001723,
			"inode_init_dir_internal() failed: %s",
			gfarm_error_string(e));
		return (e);
	}


	entry = dir_enter(inode->u.c.s.d.entries, dot, DOT_LEN, NULL);
	if (entry == NULL) {
		dir_free(inode->u.c.s.d.entries);
		gflog_debug(GFARM_MSG_1001724,
			"inode entries is NULL");
		return (GFARM_ERR_NO_MEMORY);
	}
	dir_entry_set_inode(entry, inode);

	entry = dir_enter(inode->u.c.s.d.entries, dotdot, DOTDOT_LEN,
	    NULL);
	if (entry == NULL) {
		dir_free(inode->u.c.s.d.entries);
		gflog_debug(GFARM_MSG_1001725,
			"inode entries is NULL");
		return (GFARM_ERR_NO_MEMORY);
	}
	dir_entry_set_inode(entry, parent);

	inode->i_nlink = 2;
	inode->i_mode = GFARM_S_IFDIR;
	return (GFARM_ERR_NO_ERROR);
}
