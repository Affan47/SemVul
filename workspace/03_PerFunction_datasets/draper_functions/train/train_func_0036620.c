isofss_fill_file_attrs(void *sbp, uae_u64 parent, int *dir, int *flags, TCHAR **comment, uae_u64 uniq)
{
	struct super_block *sb = (struct super_block*)sbp;
	struct inode *inode = find_inode(sb, uniq);
	if (!inode)
		return;

	*comment = NULL;
	*dir = XS_ISDIR(inode->i_mode) ? 1 : 0;
	if (inode->i_isaflags)
		*flags = inode->i_aflags;
	else
		*flags = 0;
	if (inode->i_comment)
		*comment = my_strdup(inode->i_comment);
}
