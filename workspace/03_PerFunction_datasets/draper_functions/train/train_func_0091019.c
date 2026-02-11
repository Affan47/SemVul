copy_cgroup_ns(unsigned long flags, struct user_namespace *user_ns,
	       struct cgroup_namespace *old_ns)
{
	struct cgroup_namespace *new_ns;
	struct css_set *cset;

	BUG_ON(!old_ns);

	if (!(flags & CLONE_NEWCGROUP)) {
		get_cgroup_ns(old_ns);
		return old_ns;
	}


	if (!ns_capable(user_ns, CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);

	mutex_lock(&cgroup_mutex);
	spin_lock_bh(&css_set_lock);

	cset = task_css_set(current);
	get_css_set(cset);

	spin_unlock_bh(&css_set_lock);
	mutex_unlock(&cgroup_mutex);

	new_ns = alloc_cgroup_ns();
	if (IS_ERR(new_ns)) {
		put_css_set(cset);
		return new_ns;
	}

	new_ns->user_ns = get_user_ns(user_ns);
	new_ns->root_cset = cset;

	return new_ns;
}
