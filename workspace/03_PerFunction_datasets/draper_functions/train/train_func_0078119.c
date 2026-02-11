ea_alloc_skeleton(struct gfs2_inode *ip, struct gfs2_ea_request *er,
			     unsigned int blks,
			     ea_skeleton_call_t skeleton_call, void *private)
{
	struct gfs2_alloc_parms ap = { .target = blks };
	struct buffer_head *dibh;
	int error;

	error = gfs2_rindex_update(GFS2_SB(&ip->i_inode));
	if (error)
		return error;

	error = gfs2_quota_lock_check(ip, &ap);
	if (error)
		return error;

	error = gfs2_inplace_reserve(ip, &ap);
	if (error)
		goto out_gunlock_q;

	error = gfs2_trans_begin(GFS2_SB(&ip->i_inode),
				 blks + gfs2_rg_blocks(ip, blks) +
				 RES_DINODE + RES_STATFS + RES_QUOTA, 0);
	if (error)
		goto out_ipres;

	error = skeleton_call(ip, er, private);
	if (error)
		goto out_end_trans;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (!error) {
		ip->i_inode.i_ctime = CURRENT_TIME;
		gfs2_trans_add_meta(ip->i_gl, dibh);
		gfs2_dinode_out(ip, dibh->b_data);
		brelse(dibh);
	}

out_end_trans:
	gfs2_trans_end(GFS2_SB(&ip->i_inode));
out_ipres:
	gfs2_inplace_release(ip);
out_gunlock_q:
	gfs2_quota_unlock(ip);
	return error;
}
