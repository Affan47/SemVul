ocfs2_init_locked_inode(struct inode *inode, void *opaque)
{
	struct ocfs2_find_inode_args *args = opaque;
	static struct lock_class_key ocfs2_quota_ip_alloc_sem_key,
				     ocfs2_file_ip_alloc_sem_key;

	inode->i_ino = args->fi_ino;
	OCFS2_I(inode)->ip_blkno = args->fi_blkno;
	if (args->fi_sysfile_type != 0)
		lockdep_set_class(&inode->i_mutex,
			&ocfs2_sysfile_lock_key[args->fi_sysfile_type]);
	if (args->fi_sysfile_type == USER_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == GROUP_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == LOCAL_USER_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == LOCAL_GROUP_QUOTA_SYSTEM_INODE)
		lockdep_set_class(&OCFS2_I(inode)->ip_alloc_sem,
				  &ocfs2_quota_ip_alloc_sem_key);
	else
		lockdep_set_class(&OCFS2_I(inode)->ip_alloc_sem,
				  &ocfs2_file_ip_alloc_sem_key);

	return 0;
}
