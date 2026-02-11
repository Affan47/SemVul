ocfs2_cleanup_delete_inode(struct inode *inode,
				       int sync_data)
{
	trace_ocfs2_cleanup_delete_inode(
		(unsigned long long)OCFS2_I(inode)->ip_blkno, sync_data);
	if (sync_data)
		filemap_write_and_wait(inode->i_mapping);
	truncate_inode_pages_final(&inode->i_data);
}
