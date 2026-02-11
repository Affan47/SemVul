dir_double_exhash(struct gfs2_inode *dip)
{
	struct buffer_head *dibh;
	u32 hsize;
	u32 hsize_bytes;
	__be64 *hc;
	__be64 *hc2, *h;
	int x;
	int error = 0;

	hsize = 1 << dip->i_depth;
	hsize_bytes = hsize * sizeof(__be64);

	hc = gfs2_dir_get_hash_table(dip);
	if (IS_ERR(hc))
		return PTR_ERR(hc);

	hc2 = kmalloc(hsize_bytes * 2, GFP_NOFS | __GFP_NOWARN);
	if (hc2 == NULL)
		hc2 = __vmalloc(hsize_bytes * 2, GFP_NOFS, PAGE_KERNEL);

	if (!hc2)
		return -ENOMEM;

	h = hc2;
	error = gfs2_meta_inode_buffer(dip, &dibh);
	if (error)
		goto out_kfree;

	for (x = 0; x < hsize; x++) {
		*h++ = *hc;
		*h++ = *hc;
		hc++;
	}

	error = gfs2_dir_write_data(dip, (char *)hc2, 0, hsize_bytes * 2);
	if (error != (hsize_bytes * 2))
		goto fail;

	gfs2_dir_hash_inval(dip);
	dip->i_hash_cache = hc2;
	dip->i_depth++;
	gfs2_dinode_out(dip, dibh->b_data);
	brelse(dibh);
	return 0;

fail:

	gfs2_dir_write_data(dip, (char *)hc, 0, hsize_bytes);
	i_size_write(&dip->i_inode, hsize_bytes);
	gfs2_dinode_out(dip, dibh->b_data);
	brelse(dibh);
out_kfree:
	kvfree(hc2);
	return error;
}
