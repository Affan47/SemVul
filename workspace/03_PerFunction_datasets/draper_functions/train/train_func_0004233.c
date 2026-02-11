inode_go_lock(struct gfs2_holder *gh)
{
	struct gfs2_glock *gl = gh->gh_gl;
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct gfs2_inode *ip = gl->gl_object;
	int error = 0;

	if (!ip || (gh->gh_flags & GL_SKIP))
		return 0;

	if (test_bit(GIF_INVALID, &ip->i_flags)) {
		error = gfs2_inode_refresh(ip);
		if (error)
			return error;
	}

	if (gh->gh_state != LM_ST_DEFERRED)
		inode_dio_wait(&ip->i_inode);

	if ((ip->i_diskflags & GFS2_DIF_TRUNC_IN_PROG) &&
	    (gl->gl_state == LM_ST_EXCLUSIVE) &&
	    (gh->gh_state == LM_ST_EXCLUSIVE)) {
		spin_lock(&sdp->sd_trunc_lock);
		if (list_empty(&ip->i_trunc_list))
			list_add(&sdp->sd_trunc_list, &ip->i_trunc_list);
		spin_unlock(&sdp->sd_trunc_lock);
		wake_up(&sdp->sd_quota_wait);
		return 1;
	}

	return error;
}
