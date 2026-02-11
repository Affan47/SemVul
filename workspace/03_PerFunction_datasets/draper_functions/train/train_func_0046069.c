gfs2_freeze_func(struct work_struct *work)
{
	int error;
	struct gfs2_holder freeze_gh;
	struct gfs2_sbd *sdp = container_of(work, struct gfs2_sbd, sd_freeze_work);
	struct super_block *sb = sdp->sd_vfs;

	atomic_inc(&sb->s_active);
	error = gfs2_glock_nq_init(sdp->sd_freeze_gl, LM_ST_SHARED, 0,
				   &freeze_gh);
	if (error) {
		printk(KERN_INFO "GFS2: couln't get freeze lock : %d\n", error);
		gfs2_assert_withdraw(sdp, 0);
	}
	else {
		atomic_set(&sdp->sd_freeze_state, SFS_UNFROZEN);
		error = thaw_super(sb);
		if (error) {
			printk(KERN_INFO "GFS2: couldn't thaw filesystem: %d\n",
			       error);
			gfs2_assert_withdraw(sdp, 0);
		}
		if (!test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags))
			freeze_gh.gh_flags |= GL_NOCACHE;
		gfs2_glock_dq_uninit(&freeze_gh);
	}
	deactivate_super(sb);
	return;
}
