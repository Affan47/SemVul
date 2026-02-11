gfs2_glock_iter_next(struct gfs2_glock_iter *gi)
{
	while ((gi->gl = rhashtable_walk_next(&gi->hti))) {
		if (IS_ERR(gi->gl)) {
			if (PTR_ERR(gi->gl) == -EAGAIN)
				continue;
			gi->gl = NULL;
			return;
		}

		if (gi->sdp == gi->gl->gl_name.ln_sbd &&
		    !__lockref_is_dead(&gi->gl->gl_lockref))
			return;
	}
}
