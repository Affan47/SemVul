export_encode_fh(struct inode *inode, struct fid *fid,
		int *max_len, struct inode *parent)
{
	int len = *max_len;
	int type = FILEID_INO32_GEN;

	if (parent && (len < 4)) {
		*max_len = 4;
		return FILEID_INVALID;
	} else if (len < 2) {
		*max_len = 2;
		return FILEID_INVALID;
	}

	len = 2;
	fid->i32.ino = inode->i_ino;
	fid->i32.gen = inode->i_generation;
	if (parent) {
		fid->i32.parent_ino = parent->i_ino;
		fid->i32.parent_gen = parent->i_generation;
		len = 4;
		type = FILEID_INO32_GEN_PARENT;
	}
	*max_len = len;
	return type;
}
