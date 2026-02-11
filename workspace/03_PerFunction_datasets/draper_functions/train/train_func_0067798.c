ea_read_inline(struct inode *ip, struct jfs_ea_list *ealist)
{
	struct jfs_inode_info *ji = JFS_IP(ip);
	int ea_size = sizeDXD(&ji->ea);

	if (ea_size == 0) {
		ealist->size = 0;
		return 0;
	}


	if ((sizeDXD(&ji->ea) > sizeof (ji->i_inline_ea)))
		return -EIO;
	if (le32_to_cpu(((struct jfs_ea_list *) &ji->i_inline_ea)->size)
	    != ea_size)
		return -EIO;

	memcpy(ealist, ji->i_inline_ea, ea_size);
	return 0;
}
