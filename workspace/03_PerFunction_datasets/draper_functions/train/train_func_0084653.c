gfs2_statfs_slow(struct gfs2_sbd *sdp, struct gfs2_statfs_change_host *sc)
{
	struct gfs2_rgrpd *rgd_next;
	struct gfs2_holder *gha, *gh;
	unsigned int slots = 64;
	unsigned int x;
	int done;
	int error = 0, err;

	memset(sc, 0, sizeof(struct gfs2_statfs_change_host));
	gha = kcalloc(slots, sizeof(struct gfs2_holder), GFP_KERNEL);
	if (!gha)
		return -ENOMEM;

	rgd_next = gfs2_rgrpd_get_first(sdp);

	for (;;) {
		done = 1;

		for (x = 0; x < slots; x++) {
			gh = gha + x;

			if (gh->gh_gl && gfs2_glock_poll(gh)) {
				err = gfs2_glock_wait(gh);
				if (err) {
					gfs2_holder_uninit(gh);
					error = err;
				} else {
					if (!error)
						error = statfs_slow_fill(
							gh->gh_gl->gl_object, sc);
					gfs2_glock_dq_uninit(gh);
				}
			}

			if (gh->gh_gl)
				done = 0;
			else if (rgd_next && !error) {
				error = gfs2_glock_nq_init(rgd_next->rd_gl,
							   LM_ST_SHARED,
							   GL_ASYNC,
							   gh);
				rgd_next = gfs2_rgrpd_get_next(rgd_next);
				done = 0;
			}

			if (signal_pending(current))
				error = -ERESTARTSYS;
		}

		if (done)
			break;

		yield();
	}

	kfree(gha);
	return error;
}
