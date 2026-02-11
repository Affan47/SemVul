pnfs_roc_get_barrier(struct inode *ino, u32 *barrier)
{
	struct nfs_inode *nfsi = NFS_I(ino);
	struct pnfs_layout_hdr *lo;
	u32 current_seqid;

	spin_lock(&ino->i_lock);
	lo = nfsi->layout;
	current_seqid = be32_to_cpu(lo->plh_stateid.seqid);


	*barrier = current_seqid + atomic_read(&lo->plh_outstanding);
	spin_unlock(&ino->i_lock);
}
