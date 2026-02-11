ufs_alloc_inode(struct super_block *sb)
{
	struct ufs_inode_info *ei;

	ei = kmem_cache_alloc(ufs_inode_cachep, GFP_NOFS);
	if (!ei)
		return NULL;

	ei->vfs_inode.i_version = 1;
	seqlock_init(&ei->meta_lock);
	mutex_init(&ei->truncate_mutex);
	return &ei->vfs_inode;
}
