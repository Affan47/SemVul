omfs_fill_chain(struct inode *dir, struct dir_context *ctx,
		u64 fsblock, int hindex)
{

	while (fsblock != ~0) {
		struct buffer_head *bh = omfs_bread(dir->i_sb, fsblock);
		struct omfs_inode *oi;
		u64 self;
		unsigned char d_type;

		if (!bh)
			return true;

		oi = (struct omfs_inode *) bh->b_data;
		if (omfs_is_bad(OMFS_SB(dir->i_sb), &oi->i_head, fsblock)) {
			brelse(bh);
			return true;
		}

		self = fsblock;
		fsblock = be64_to_cpu(oi->i_sibling);


		if (hindex) {
			hindex--;
			brelse(bh);
			continue;
		}

		d_type = (oi->i_type == OMFS_DIR) ? DT_DIR : DT_REG;

		if (!dir_emit(ctx, oi->i_name,
			      strnlen(oi->i_name, OMFS_NAMELEN),
			      self, d_type)) {
			brelse(bh);
			return false;
		}
		brelse(bh);
		ctx->pos++;
	}
	return true;
}
