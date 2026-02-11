kill_css(struct cgroup_subsys_state *css)
{
	lockdep_assert_held(&cgroup_mutex);


	css_clear_dir(css, NULL);


	css_get(css);


	percpu_ref_kill_and_confirm(&css->refcnt, css_killed_ref_fn);
}
