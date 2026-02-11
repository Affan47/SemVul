nfs_readpage_done(struct rpc_task *task,
			     struct nfs_pgio_header *hdr,
			     struct inode *inode)
{
	int status = NFS_PROTO(inode)->read_done(task, hdr);
	if (status != 0)
		return status;

	nfs_add_stats(inode, NFSIOS_SERVERREADBYTES, hdr->res.count);

	if (task->tk_status == -ESTALE) {
		set_bit(NFS_INO_STALE, &NFS_I(inode)->flags);
		nfs_mark_for_revalidate(inode);
	}
	return 0;
}
