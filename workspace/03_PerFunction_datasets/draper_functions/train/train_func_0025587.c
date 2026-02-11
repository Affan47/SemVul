do_promote(struct gfs2_glock *gl)
__releases(&gl->gl_lockref.lock)
__acquires(&gl->gl_lockref.lock)
{
	const struct gfs2_glock_operations *glops = gl->gl_ops;
	struct gfs2_holder *gh, *tmp;
	int ret;

restart:
	list_for_each_entry_safe(gh, tmp, &gl->gl_holders, gh_list) {
		if (test_bit(HIF_HOLDER, &gh->gh_iflags))
			continue;
		if (may_grant(gl, gh)) {
			if (gh->gh_list.prev == &gl->gl_holders &&
			    glops->go_lock) {
				spin_unlock(&gl->gl_lockref.lock);

				ret = glops->go_lock(gh);
				spin_lock(&gl->gl_lockref.lock);
				if (ret) {
					if (ret == 1)
						return 2;
					gh->gh_error = ret;
					list_del_init(&gh->gh_list);
					trace_gfs2_glock_queue(gh, 0);
					gfs2_holder_wake(gh);
					goto restart;
				}
				set_bit(HIF_HOLDER, &gh->gh_iflags);
				trace_gfs2_promote(gh, 1);
				gfs2_holder_wake(gh);
				goto restart;
			}
			set_bit(HIF_HOLDER, &gh->gh_iflags);
			trace_gfs2_promote(gh, 0);
			gfs2_holder_wake(gh);
			continue;
		}
		if (gh->gh_list.prev == &gl->gl_holders)
			return 1;
		do_error(gl, 0);
		break;
	}
	return 0;
}
