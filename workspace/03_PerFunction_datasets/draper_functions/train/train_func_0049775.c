nfs_post_op_update_inode_locked(struct inode *inode, struct nfs_fattr *fattr)
{
	unsigned long invalid = NFS_INO_INVALID_ATTR|NFS_INO_REVAL_PAGECACHE;


	if (NFS_PROTO(inode)->have_delegation(inode, FMODE_READ))
		invalid = NFS_INO_INVALID_ATTR|NFS_INO_REVAL_FORCED;

	if (S_ISDIR(inode->i_mode))
		invalid |= NFS_INO_INVALID_DATA;
	nfs_set_cache_invalid(inode, invalid);
	if ((fattr->valid & NFS_ATTR_FATTR) == 0)
		return 0;
	return nfs_refresh_inode_locked(inode, fattr);
}
