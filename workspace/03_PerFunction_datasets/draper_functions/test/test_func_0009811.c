nfs_pageio_init_write(struct nfs_pageio_descriptor *pgio,
			       struct inode *inode, int ioflags, bool force_mds,
			       const struct nfs_pgio_completion_ops *compl_ops)
{
	struct nfs_server *server = NFS_SERVER(inode);
	const struct nfs_pageio_ops *pg_ops = &nfs_pgio_rw_ops;

#ifdef CONFIG_NFS_V4_1
	if (server->pnfs_curr_ld && !force_mds)
		pg_ops = server->pnfs_curr_ld->pg_write_ops;
#endif
	nfs_pageio_init(pgio, inode, pg_ops, compl_ops, &nfs_rw_write_ops,
			server->wsize, ioflags);
}
