gfs2_gl_hash_clear(struct gfs2_sbd *sdp)
{
	set_bit(SDF_SKIP_DLM_UNLOCK, &sdp->sd_flags);
	flush_workqueue(glock_workqueue);
	glock_hash_walk(clear_glock, sdp);
	flush_workqueue(glock_workqueue);
	wait_event(sdp->sd_glock_wait, atomic_read(&sdp->sd_glock_disposal) == 0);
	glock_hash_walk(dump_glock_func, sdp);
}
