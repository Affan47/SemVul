fat16_ent_put(struct fat_entry *fatent, int new)
{
	if (new == FAT_ENT_EOF)
		new = EOF_FAT16;

	*fatent->u.ent16_p = cpu_to_le16(new);
	mark_buffer_dirty_inode(fatent->bhs[0], fatent->fat_inode);
}
