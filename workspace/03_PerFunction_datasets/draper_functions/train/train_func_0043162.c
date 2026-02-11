fix_one_directory_exhash(struct gfs2_sbd *sbp, struct gfs2_inode *dip, uint64_t dentmod)
{
	struct gfs2_buffer_head *bh_leaf;
	int error;
	uint64_t leaf_block, prev_leaf_block;
	uint32_t leaf_num;

	prev_leaf_block = 0;

	for (leaf_num = 0; ; leaf_num++) {
		uint64_t buf;
		struct gfs2_leaf leaf;

		error = gfs2_readi(dip, (char *)&buf, leaf_num * sizeof(uint64_t),
						   sizeof(uint64_t));
		if (!error)
			return 0;
		else if (error != sizeof(uint64_t)) {
			log_crit(_("fix_one_directory_exhash: error reading directory.\n"));
			return -1;
		}
		else {
			leaf_block = be64_to_cpu(buf);
			error = 0;
		}
	leaf_chain:

		if (leaf_block == prev_leaf_block)
			continue;

		prev_leaf_block = leaf_block;

		error = gfs2_get_leaf(dip, leaf_block, &bh_leaf);
		if (error) {
			log_crit(_("Error reading leaf %llx\n"),
				 (unsigned long long)leaf_block);
			break;
		}
		gfs2_leaf_in(&leaf, bh_leaf);
		error = process_dirent_info(dip, sbp, bh_leaf, leaf.lf_entries, dentmod);
		bmodified(bh_leaf);
		brelse(bh_leaf);
		if (dentmod && error == -EISDIR)
			break;
		if (leaf.lf_next) {
			leaf_block = leaf.lf_next;
			error = 0;
			goto leaf_chain;
		}
	}
	return 0;
}
