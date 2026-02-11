btrfs_raid_unplug(struct blk_plug_cb *cb, bool from_schedule)
{
	struct btrfs_plug_cb *plug;
	plug = container_of(cb, struct btrfs_plug_cb, cb);

	if (from_schedule) {
		btrfs_init_work(&plug->work, btrfs_rmw_helper,
				unplug_work, NULL, NULL);
		btrfs_queue_work(plug->info->rmw_workers,
				 &plug->work);
		return;
	}
	run_plug(plug);
}
