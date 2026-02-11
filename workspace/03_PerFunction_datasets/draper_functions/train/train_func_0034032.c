ubifs_tnc_start_commit(struct ubifs_info *c, struct ubifs_zbranch *zroot)
{
	int err = 0, cnt;

	mutex_lock(&c->tnc_mutex);
	err = dbg_check_tnc(c, 1);
	if (err)
		goto out;
	cnt = get_znodes_to_commit(c);
	if (cnt != 0) {
		int no_space = 0;

		err = alloc_idx_lebs(c, cnt);
		if (err == -ENOSPC)
			no_space = 1;
		else if (err)
			goto out_free;
		err = layout_commit(c, no_space, cnt);
		if (err)
			goto out_free;
		ubifs_assert(atomic_long_read(&c->dirty_zn_cnt) == 0);
		err = free_unused_idx_lebs(c);
		if (err)
			goto out;
	}
	destroy_old_idx(c);
	memcpy(zroot, &c->zroot, sizeof(struct ubifs_zbranch));

	err = ubifs_save_dirty_idx_lnums(c);
	if (err)
		goto out;

	spin_lock(&c->space_lock);


	ubifs_assert(c->bi.min_idx_lebs == ubifs_calc_min_idx_lebs(c));
	c->bi.old_idx_sz = c->calc_idx_sz;
	c->bi.uncommitted_idx = 0;
	c->bi.min_idx_lebs = ubifs_calc_min_idx_lebs(c);
	spin_unlock(&c->space_lock);
	mutex_unlock(&c->tnc_mutex);

	dbg_cmt("number of index LEBs %d", c->lst.idx_lebs);
	dbg_cmt("size of index %llu", c->calc_idx_sz);
	return err;

out_free:
	free_idx_lebs(c);
out:
	mutex_unlock(&c->tnc_mutex);
	return err;
}
