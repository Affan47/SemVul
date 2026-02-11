smb2_wp_retry_size(struct inode *inode)
{
	return min_t(unsigned int, CIFS_SB(inode->i_sb)->wsize,
		     SMB2_MAX_BUFFER_SIZE);
}
