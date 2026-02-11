cgroup_remount(struct kernfs_root *kf_root, int *flags, char *data)
{
	int ret = 0;
	struct cgroup_root *root = cgroup_root_from_kf(kf_root);
	struct cgroup_sb_opts opts;
	unsigned long added_mask, removed_mask;

	if (root == &cgrp_dfl_root) {
		pr_err("remount is not allowed\n");
		return -EINVAL;
	}

	mutex_lock(&cgroup_mutex);


	ret = parse_cgroupfs_options(data, &opts);
	if (ret)
		goto out_unlock;

	if (opts.subsys_mask != root->subsys_mask || opts.release_agent)
		pr_warn("option changes via remount are deprecated (pid=%d comm=%s)\n",
			task_tgid_nr(current), current->comm);

	added_mask = opts.subsys_mask & ~root->subsys_mask;
	removed_mask = root->subsys_mask & ~opts.subsys_mask;


	if ((opts.flags ^ root->flags) ||
	    (opts.name && strcmp(opts.name, root->name))) {
		pr_err("option or name mismatch, new: 0x%x \"%s\", old: 0x%x \"%s\"\n",
		       opts.flags, opts.name ?: "", root->flags, root->name);
		ret = -EINVAL;
		goto out_unlock;
	}


	if (!list_empty(&root->cgrp.self.children)) {
		ret = -EBUSY;
		goto out_unlock;
	}

	ret = rebind_subsystems(root, added_mask);
	if (ret)
		goto out_unlock;

	rebind_subsystems(&cgrp_dfl_root, removed_mask);

	if (opts.release_agent) {
		spin_lock(&release_agent_path_lock);
		strcpy(root->release_agent_path, opts.release_agent);
		spin_unlock(&release_agent_path_lock);
	}
 out_unlock:
	kfree(opts.release_agent);
	kfree(opts.name);
	mutex_unlock(&cgroup_mutex);
	return ret;
}
