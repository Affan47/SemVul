inode_go_inval(struct gfs2_glock *gl, int flags)
{
	struct gfs2_inode *ip = gl->gl_object;

	gfs2_assert_withdraw(gl->gl_name.ln_sbd, !atomic_read(&gl->gl_ail_count));

	if (flags & DIO_METADATA) {
		struct address_space *mapping = gfs2_glock2aspace(gl);
		truncate_inode_pages(mapping, 0);
		if (ip) {
			set_bit(GIF_INVALID, &ip->i_flags);
			forget_all_cached_acls(&ip->i_inode);
			gfs2_dir_hash_inval(ip);
		}
	}

	if (ip == GFS2_I(gl->gl_name.ln_sbd->sd_rindex)) {
		gfs2_log_flush(gl->gl_name.ln_sbd, NULL, NORMAL_FLUSH);
		gl->gl_name.ln_sbd->sd_rindex_uptodate = 0;
	}
	if (ip && S_ISREG(ip->i_inode.i_mode))
		truncate_inode_pages(ip->i_inode.i_mapping, 0);
}
