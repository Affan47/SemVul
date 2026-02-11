nfs_mapping_need_revalidate_inode(struct inode *inode)
{
	if (nfs_have_delegated_attributes(inode))
		return false;
	return (NFS_I(inode)->cache_validity & NFS_INO_REVAL_PAGECACHE)
		|| nfs_attribute_timeout(inode)
		|| NFS_STALE(inode);
}
