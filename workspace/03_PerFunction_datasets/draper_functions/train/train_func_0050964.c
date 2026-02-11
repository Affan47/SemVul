ocfs2_init_local_system_inodes(struct ocfs2_super *osb)
{
	struct inode *new = NULL;
	int status = 0;
	int i;

	for (i = OCFS2_LAST_GLOBAL_SYSTEM_INODE + 1;
	     i < NUM_SYSTEM_INODES;
	     i++) {
		if (!ocfs2_need_system_inode(osb, i))
			continue;
		new = ocfs2_get_system_file_inode(osb, i, osb->slot_num);
		if (!new) {
			ocfs2_release_system_inodes(osb);
			status = -EINVAL;
			mlog(ML_ERROR, "status=%d, sysfile=%d, slot=%d\n",
			     status, i, osb->slot_num);
			goto bail;
		}

		iput(new);
	}

bail:
	if (status)
		mlog_errno(status);
	return status;
}
