dir_e_read(struct inode *inode, struct dir_context *ctx,
		      struct file_ra_state *f_ra)
{
	struct gfs2_inode *dip = GFS2_I(inode);
	u32 hsize, len = 0;
	u32 hash, index;
	__be64 *lp;
	int copied = 0;
	int error = 0;
	unsigned depth = 0;

	hsize = 1 << dip->i_depth;
	hash = gfs2_dir_offset2hash(ctx->pos);
	index = hash >> (32 - dip->i_depth);

	if (dip->i_hash_cache == NULL)
		f_ra->start = 0;
	lp = gfs2_dir_get_hash_table(dip);
	if (IS_ERR(lp))
		return PTR_ERR(lp);

	gfs2_dir_readahead(inode, hsize, index, f_ra);

	while (index < hsize) {
		error = gfs2_dir_read_leaf(inode, ctx,
					   &copied, &depth,
					   be64_to_cpu(lp[index]));
		if (error)
			break;

		len = 1 << (dip->i_depth - depth);
		index = (index & ~(len - 1)) + len;
	}

	if (error > 0)
		error = 0;
	return error;
}
