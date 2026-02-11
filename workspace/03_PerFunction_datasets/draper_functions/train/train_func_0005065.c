fat_get_entry(struct inode *dir, loff_t *pos,
				struct buffer_head **bh,
				struct msdos_dir_entry **de)
{

	if (*bh && *de &&
	   (*de - (struct msdos_dir_entry *)(*bh)->b_data) <
				MSDOS_SB(dir->i_sb)->dir_per_block - 1) {
		*pos += sizeof(struct msdos_dir_entry);
		(*de)++;
		return 0;
	}
	return fat__get_entry(dir, pos, bh, de);
}
