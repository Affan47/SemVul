btrfs_qgroup_free_refroot(struct btrfs_fs_info *fs_info,
			       u64 ref_root, u64 num_bytes)
{
	struct btrfs_root *quota_root;
	struct btrfs_qgroup *qgroup;
	struct ulist_node *unode;
	struct ulist_iterator uiter;
	int ret = 0;

	if (!is_fstree(ref_root))
		return;

	if (num_bytes == 0)
		return;

	spin_lock(&fs_info->qgroup_lock);

	quota_root = fs_info->quota_root;
	if (!quota_root)
		goto out;

	qgroup = find_qgroup_rb(fs_info, ref_root);
	if (!qgroup)
		goto out;

	ulist_reinit(fs_info->qgroup_ulist);
	ret = ulist_add(fs_info->qgroup_ulist, qgroup->qgroupid,
			(uintptr_t)qgroup, GFP_ATOMIC);
	if (ret < 0)
		goto out;
	ULIST_ITER_INIT(&uiter);
	while ((unode = ulist_next(fs_info->qgroup_ulist, &uiter))) {
		struct btrfs_qgroup *qg;
		struct btrfs_qgroup_list *glist;

		qg = u64_to_ptr(unode->aux);

		qg->reserved -= num_bytes;

		list_for_each_entry(glist, &qg->groups, next_group) {
			ret = ulist_add(fs_info->qgroup_ulist,
					glist->group->qgroupid,
					(uintptr_t)glist->group, GFP_ATOMIC);
			if (ret < 0)
				goto out;
		}
	}

out:
	spin_unlock(&fs_info->qgroup_lock);
}
