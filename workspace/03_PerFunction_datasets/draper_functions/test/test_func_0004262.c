close_ctree(struct btrfs_root *root)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	int ret;

	fs_info->closing = 1;
	smp_mb();


	btrfs_qgroup_wait_for_completion(fs_info, false);


	down(&fs_info->uuid_tree_rescan_sem);

	up(&fs_info->uuid_tree_rescan_sem);


	btrfs_pause_balance(fs_info);

	btrfs_dev_replace_suspend_for_unmount(fs_info);

	btrfs_scrub_cancel(fs_info);


	wait_event(fs_info->transaction_wait,
		   (atomic_read(&fs_info->defrag_running) == 0));


	btrfs_cleanup_defrag_inodes(fs_info);

	cancel_work_sync(&fs_info->async_reclaim_work);

	if (!(fs_info->sb->s_flags & MS_RDONLY)) {


		btrfs_delete_unused_bgs(root->fs_info);

		ret = btrfs_commit_super(root);
		if (ret)
			btrfs_err(fs_info, "commit super ret %d", ret);
	}

	if (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state))
		btrfs_error_commit_super(root);

	kthread_stop(fs_info->transaction_kthread);
	kthread_stop(fs_info->cleaner_kthread);

	fs_info->closing = 2;
	smp_mb();

	btrfs_free_qgroup_config(fs_info);

	if (percpu_counter_sum(&fs_info->delalloc_bytes)) {
		btrfs_info(fs_info, "at unmount delalloc count %lld",
		       percpu_counter_sum(&fs_info->delalloc_bytes));
	}

	btrfs_sysfs_remove_mounted(fs_info);
	btrfs_sysfs_remove_fsid(fs_info->fs_devices);

	btrfs_free_fs_roots(fs_info);

	btrfs_put_block_group_cache(fs_info);

	btrfs_free_block_groups(fs_info);


	invalidate_inode_pages2(fs_info->btree_inode->i_mapping);
	btrfs_stop_all_workers(fs_info);

	fs_info->open = 0;
	free_root_pointers(fs_info, 1);

	iput(fs_info->btree_inode);

#ifdef CONFIG_BTRFS_FS_CHECK_INTEGRITY
	if (btrfs_test_opt(root, CHECK_INTEGRITY))
		btrfsic_unmount(root, fs_info->fs_devices);
#endif

	btrfs_close_devices(fs_info->fs_devices);
	btrfs_mapping_tree_free(&fs_info->mapping_tree);

	percpu_counter_destroy(&fs_info->dirty_metadata_bytes);
	percpu_counter_destroy(&fs_info->delalloc_bytes);
	percpu_counter_destroy(&fs_info->bio_counter);
	bdi_destroy(&fs_info->bdi);
	cleanup_srcu_struct(&fs_info->subvol_srcu);

	btrfs_free_stripe_hash_table(fs_info);

	__btrfs_free_block_rsv(root->orphan_block_rsv);
	root->orphan_block_rsv = NULL;

	lock_chunks(root);
	while (!list_empty(&fs_info->pinned_chunks)) {
		struct extent_map *em;

		em = list_first_entry(&fs_info->pinned_chunks,
				      struct extent_map, list);
		list_del_init(&em->list);
		free_extent_map(em);
	}
	unlock_chunks(root);
}
