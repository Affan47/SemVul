pr_cont_kernfs_path(struct kernfs_node *kn)
{
	unsigned long flags;
	int sz;

	spin_lock_irqsave(&kernfs_rename_lock, flags);

	sz = kernfs_path_from_node_locked(kn, NULL, kernfs_pr_cont_buf,
					  sizeof(kernfs_pr_cont_buf));
	if (sz < 0) {
		pr_cont("(error)");
		goto out;
	}

	if (sz >= sizeof(kernfs_pr_cont_buf)) {
		pr_cont("(name too long)");
		goto out;
	}

	pr_cont("%s", kernfs_pr_cont_buf);

out:
	spin_unlock_irqrestore(&kernfs_rename_lock, flags);
}
