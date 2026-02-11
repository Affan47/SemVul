reada_start_machine(struct btrfs_fs_info *fs_info)
{
	struct reada_machine_work *rmw;

	rmw = kzalloc(sizeof(*rmw), GFP_NOFS);
	if (!rmw) {

		BUG();
	}
	btrfs_init_work(&rmw->work, btrfs_readahead_helper,
			reada_start_machine_worker, NULL, NULL);
	rmw->fs_info = fs_info;

	btrfs_queue_work(fs_info->readahead_workers, &rmw->work);
}
