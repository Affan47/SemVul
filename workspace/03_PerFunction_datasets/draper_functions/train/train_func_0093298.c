mem_cgroup_iter(struct mem_cgroup *root,
				   struct mem_cgroup *prev,
				   struct mem_cgroup_reclaim_cookie *reclaim)
{
	struct mem_cgroup_reclaim_iter *uninitialized_var(iter);
	struct cgroup_subsys_state *css = NULL;
	struct mem_cgroup *memcg = NULL;
	struct mem_cgroup *pos = NULL;

	if (mem_cgroup_disabled())
		return NULL;

	if (!root)
		root = root_mem_cgroup;

	if (prev && !reclaim)
		pos = prev;

	if (!root->use_hierarchy && root != root_mem_cgroup) {
		if (prev)
			goto out;
		return root;
	}

	rcu_read_lock();

	if (reclaim) {
		struct mem_cgroup_per_zone *mz;

		mz = mem_cgroup_zone_zoneinfo(root, reclaim->zone);
		iter = &mz->iter[reclaim->priority];

		if (prev && reclaim->generation != iter->generation)
			goto out_unlock;

		while (1) {
			pos = READ_ONCE(iter->position);
			if (!pos || css_tryget(&pos->css))
				break;


			(void)cmpxchg(&iter->position, pos, NULL);
		}
	}

	if (pos)
		css = &pos->css;

	for (;;) {
		css = css_next_descendant_pre(css, &root->css);
		if (!css) {


			if (!prev)
				continue;
			break;
		}


		memcg = mem_cgroup_from_css(css);

		if (css == &root->css)
			break;

		if (css_tryget(css)) {


			if (smp_load_acquire(&memcg->initialized))
				break;

			css_put(css);
		}

		memcg = NULL;
	}

	if (reclaim) {


		(void)cmpxchg(&iter->position, pos, memcg);

		if (pos)
			css_put(&pos->css);

		if (!memcg)
			iter->generation++;
		else if (!prev)
			reclaim->generation = iter->generation;
	}

out_unlock:
	rcu_read_unlock();
out:
	if (prev && prev != root)
		css_put(&prev->css);

	return memcg;
}
