dir_e_search(struct gfs2_inode *dip, const char *filename,
			int len, unsigned int *type, struct gfs2_inum *inum)
{
	struct gfs2_buffer_head *bh = NULL;
	struct gfs2_dirent *dent;
	int error;

	error = linked_leaf_search(dip, filename, len, &dent, &bh);
	if (error)
		return error;

	gfs2_inum_in(inum, (char *)&dent->de_inum);
	if (type)
		*type = be16_to_cpu(dent->de_type);

	brelse(bh);

	return 0;
}
