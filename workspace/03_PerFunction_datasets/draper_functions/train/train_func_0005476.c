nfs_revalidate_file_size(struct inode *inode, struct file *filp)
{
	struct nfs_server *server = NFS_SERVER(inode);
	struct nfs_inode *nfsi = NFS_I(inode);

	if (nfs_have_delegated_attributes(inode))
		goto out_noreval;

	if (filp->f_flags & O_DIRECT)
		goto force_reval;
	if (nfsi->cache_validity & NFS_INO_REVAL_PAGECACHE)
		goto force_reval;
	if (nfs_attribute_timeout(inode))
		goto force_reval;
out_noreval:
	return 0;
force_reval:
	return __nfs_revalidate_inode(server, inode);
}
