ncp_instantiate(struct inode *dir, struct dentry *dentry,
			struct ncp_entry_info *finfo)
{
	struct inode *inode;
	int error = -EINVAL;

	finfo->ino = iunique(dir->i_sb, 2);
	inode = ncp_iget(dir->i_sb, finfo);
	if (!inode)
		goto out_close;
	d_instantiate(dentry,inode);
	error = 0;
out:
	return error;

out_close:
	ncp_vdbg("%pd2 failed, closing file\n", dentry);
	ncp_close_file(NCP_SERVER(dir), finfo->file_handle);
	goto out;
}
