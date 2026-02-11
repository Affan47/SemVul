check_leaf_eattr(struct gfs2_inode *ip, uint64_t block,
			    uint64_t parent, struct metawalk_fxns *pass)
{
	struct gfs2_buffer_head *bh = NULL;

	if (pass->check_eattr_leaf) {
		int error = 0;

		log_debug( _("Checking EA leaf block #%llu (0x%llx).\n"),
			   (unsigned long long)block,
			   (unsigned long long)block);

		error = pass->check_eattr_leaf(ip, block, parent, &bh,
					       pass->private);
		if (error < 0) {
			stack;
			return -1;
		}
		if (error > 0) {
			if (bh)
				brelse(bh);
			return 1;
		}
		if (bh) {
			error = check_eattr_entries(ip, bh, pass);
			brelse(bh);
		}
		return error;
	}

	return 0;
}
