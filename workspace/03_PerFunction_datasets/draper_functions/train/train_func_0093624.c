nfs_unblock_sillyrename(struct dentry *dentry)
{
	struct inode *dir = d_inode(dentry);
	struct nfs_inode *nfsi = NFS_I(dir);
	struct nfs_unlinkdata *data;

	atomic_inc(&nfsi->silly_count);
	spin_lock(&dir->i_lock);
	while (!hlist_empty(&nfsi->silly_list)) {
		if (!atomic_inc_not_zero(&nfsi->silly_count))
			break;
		data = hlist_entry(nfsi->silly_list.first, struct nfs_unlinkdata, list);
		hlist_del(&data->list);
		spin_unlock(&dir->i_lock);
		if (nfs_do_call_unlink(dentry, dir, data) == 0)
			nfs_free_unlinkdata(data);
		spin_lock(&dir->i_lock);
	}
	spin_unlock(&dir->i_lock);
}
