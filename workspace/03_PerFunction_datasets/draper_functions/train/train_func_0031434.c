css_rightmost_descendant(struct cgroup_subsys_state *pos)
{
	struct cgroup_subsys_state *last, *tmp;

	cgroup_assert_mutex_or_rcu_locked();

	do {
		last = pos;

		pos = NULL;
		css_for_each_child(tmp, last)
			pos = tmp;
	} while (pos);

	return last;
}
