au_write_post(struct inode *inode, struct file *h_file,
			  struct au_write_pre *wpre, ssize_t written)
{
	struct inode *h_inode;

	au_cpup_attr_timesizes(inode);
	AuDebugOn(au_ibstart(inode) != wpre->bstart);
	h_inode = file_inode(h_file);
	inode->i_mode = h_inode->i_mode;
	ii_write_unlock(inode);
	fput(h_file);


	if (written > 0)
		au_fhsm_wrote(inode->i_sb, wpre->bstart,
			      h_inode->i_blocks > wpre->blks);
}
