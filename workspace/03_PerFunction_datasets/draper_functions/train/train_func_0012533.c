btrfs_limit_qgroup(struct btrfs_trans_handle *trans,
		       struct btrfs_fs_info *fs_info, u64 qgroupid,
		       struct btrfs_qgroup_limit *limit)
{
	struct btrfs_root *quota_root;
	struct btrfs_qgroup *qgroup;
	int ret = 0;


	const u64 CLEAR_VALUE = -1;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	quota_root = fs_info->quota_root;
	if (!quota_root) {
		ret = -EINVAL;
		goto out;
	}

	qgroup = find_qgroup_rb(fs_info, qgroupid);
	if (!qgroup) {
		ret = -ENOENT;
		goto out;
	}

	spin_lock(&fs_info->qgroup_lock);
	if (limit->flags & BTRFS_QGROUP_LIMIT_MAX_RFER) {
		if (limit->max_rfer == CLEAR_VALUE) {
			qgroup->lim_flags &= ~BTRFS_QGROUP_LIMIT_MAX_RFER;
			limit->flags &= ~BTRFS_QGROUP_LIMIT_MAX_RFER;
			qgroup->max_rfer = 0;
		} else {
			qgroup->max_rfer = limit->max_rfer;
		}
	}
	if (limit->flags & BTRFS_QGROUP_LIMIT_MAX_EXCL) {
		if (limit->max_excl == CLEAR_VALUE) {
			qgroup->lim_flags &= ~BTRFS_QGROUP_LIMIT_MAX_EXCL;
			limit->flags &= ~BTRFS_QGROUP_LIMIT_MAX_EXCL;
			qgroup->max_excl = 0;
		} else {
			qgroup->max_excl = limit->max_excl;
		}
	}
	if (limit->flags & BTRFS_QGROUP_LIMIT_RSV_RFER) {
		if (limit->rsv_rfer == CLEAR_VALUE) {
			qgroup->lim_flags &= ~BTRFS_QGROUP_LIMIT_RSV_RFER;
			limit->flags &= ~BTRFS_QGROUP_LIMIT_RSV_RFER;
			qgroup->rsv_rfer = 0;
		} else {
			qgroup->rsv_rfer = limit->rsv_rfer;
		}
	}
	if (limit->flags & BTRFS_QGROUP_LIMIT_RSV_EXCL) {
		if (limit->rsv_excl == CLEAR_VALUE) {
			qgroup->lim_flags &= ~BTRFS_QGROUP_LIMIT_RSV_EXCL;
			limit->flags &= ~BTRFS_QGROUP_LIMIT_RSV_EXCL;
			qgroup->rsv_excl = 0;
		} else {
			qgroup->rsv_excl = limit->rsv_excl;
		}
	}
	qgroup->lim_flags |= limit->flags;

	spin_unlock(&fs_info->qgroup_lock);

	ret = update_qgroup_limit_item(trans, quota_root, qgroup);
	if (ret) {
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
		btrfs_info(fs_info, "unable to update quota limit for %llu",
		       qgroupid);
	}

out:
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	return ret;
}
