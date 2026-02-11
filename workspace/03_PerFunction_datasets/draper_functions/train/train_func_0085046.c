nfs_dec_sillycount(struct inode *dir)
{
	struct nfs_inode *nfsi = NFS_I(dir);
	if (atomic_dec_return(&nfsi->silly_count) == 1)
		wake_up(&nfsi->waitqueue);
}
