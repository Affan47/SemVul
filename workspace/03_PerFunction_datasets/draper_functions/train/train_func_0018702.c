btrfs_alloc_data_chunk_ondemand(struct inode *inode, u64 bytes)
{
	struct btrfs_space_info *data_sinfo;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_fs_info *fs_info = root->fs_info;
	u64 used;
	int ret = 0;
	int need_commit = 2;
	int have_pinned_space;


	bytes = ALIGN(bytes, root->sectorsize);

	if (btrfs_is_free_space_inode(inode)) {
		need_commit = 0;
		ASSERT(current->journal_info);
	}

	data_sinfo = fs_info->data_sinfo;
	if (!data_sinfo)
		goto alloc;

again:

	spin_lock(&data_sinfo->lock);
	used = data_sinfo->bytes_used + data_sinfo->bytes_reserved +
		data_sinfo->bytes_pinned + data_sinfo->bytes_readonly +
		data_sinfo->bytes_may_use;

	if (used + bytes > data_sinfo->total_bytes) {
		struct btrfs_trans_handle *trans;


		if (!data_sinfo->full) {
			u64 alloc_target;

			data_sinfo->force_alloc = CHUNK_ALLOC_FORCE;
			spin_unlock(&data_sinfo->lock);
alloc:
			alloc_target = btrfs_get_alloc_profile(root, 1);


			trans = btrfs_join_transaction(root);
			if (IS_ERR(trans))
				return PTR_ERR(trans);

			ret = do_chunk_alloc(trans, root->fs_info->extent_root,
					     alloc_target,
					     CHUNK_ALLOC_NO_FORCE);
			btrfs_end_transaction(trans, root);
			if (ret < 0) {
				if (ret != -ENOSPC)
					return ret;
				else {
					have_pinned_space = 1;
					goto commit_trans;
				}
			}

			if (!data_sinfo)
				data_sinfo = fs_info->data_sinfo;

			goto again;
		}


		have_pinned_space = percpu_counter_compare(
			&data_sinfo->total_bytes_pinned,
			used + bytes - data_sinfo->total_bytes);
		spin_unlock(&data_sinfo->lock);


commit_trans:
		if (need_commit &&
		    !atomic_read(&root->fs_info->open_ioctl_trans)) {
			need_commit--;

			if (need_commit > 0) {
				btrfs_start_delalloc_roots(fs_info, 0, -1);
				btrfs_wait_ordered_roots(fs_info, -1);
			}

			trans = btrfs_join_transaction(root);
			if (IS_ERR(trans))
				return PTR_ERR(trans);
			if (have_pinned_space >= 0 ||
			    test_bit(BTRFS_TRANS_HAVE_FREE_BGS,
				     &trans->transaction->flags) ||
			    need_commit > 0) {
				ret = btrfs_commit_transaction(trans, root);
				if (ret)
					return ret;


				mutex_lock(&root->fs_info->cleaner_delayed_iput_mutex);
				mutex_unlock(&root->fs_info->cleaner_delayed_iput_mutex);
				goto again;
			} else {
				btrfs_end_transaction(trans, root);
			}
		}

		trace_btrfs_space_reservation(root->fs_info,
					      "space_info:enospc",
					      data_sinfo->flags, bytes, 1);
		return -ENOSPC;
	}
	data_sinfo->bytes_may_use += bytes;
	trace_btrfs_space_reservation(root->fs_info, "space_info",
				      data_sinfo->flags, bytes, 1);
	spin_unlock(&data_sinfo->lock);

	return ret;
}
