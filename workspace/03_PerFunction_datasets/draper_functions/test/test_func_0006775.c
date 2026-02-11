ocfs2_alloc_inode(struct super_block *sb)
{
	struct ocfs2_inode_info *oi;

	oi = kmem_cache_alloc(ocfs2_inode_cachep, GFP_NOFS);
	if (!oi)
		return NULL;

	oi->i_sync_tid = 0;
	oi->i_datasync_tid = 0;
	memset(&oi->i_dquot, 0, sizeof(oi->i_dquot));

	jbd2_journal_init_jbd_inode(&oi->ip_jinode, &oi->vfs_inode);
	return &oi->vfs_inode;
}
