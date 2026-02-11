smb3_punch_hole(struct file *file, struct cifs_tcon *tcon,
			    loff_t offset, loff_t len)
{
	struct inode *inode;
	struct cifsInodeInfo *cifsi;
	struct cifsFileInfo *cfile = file->private_data;
	struct file_zero_data_information fsctl_buf;
	long rc;
	unsigned int xid;
	__u8 set_sparse = 1;

	xid = get_xid();

	inode = d_inode(cfile->dentry);
	cifsi = CIFS_I(inode);


	if (!smb2_set_sparse(xid, tcon, cfile, inode, set_sparse))
		return -EOPNOTSUPP;

	cifs_dbg(FYI, "offset %lld len %lld", offset, len);

	fsctl_buf.FileOffset = cpu_to_le64(offset);
	fsctl_buf.BeyondFinalZero = cpu_to_le64(offset + len);

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.volatile_fid, FSCTL_SET_ZERO_DATA,
			true , (char *)&fsctl_buf,
			sizeof(struct file_zero_data_information), NULL, NULL);
	free_xid(xid);
	return rc;
}
