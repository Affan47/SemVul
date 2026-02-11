ceph_writeback_work(struct work_struct *work)
{
	struct ceph_inode_info *ci = container_of(work, struct ceph_inode_info,
						  i_wb_work);
	struct inode *inode = &ci->vfs_inode;

	dout("writeback %p\n", inode);
	filemap_fdatawrite(&inode->i_data);
	iput(inode);
}
