__reada_start_machine(struct btrfs_fs_info *fs_info)
{
	struct btrfs_device *device;
	struct btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	u64 enqueued;
	u64 total = 0;
	int i;

	do {
		enqueued = 0;
		list_for_each_entry(device, &fs_devices->devices, dev_list) {
			if (atomic_read(&device->reada_in_flight) <
			    MAX_IN_FLIGHT)
				enqueued += reada_start_machine_dev(fs_info,
								    device);
		}
		total += enqueued;
	} while (enqueued && total < 10000);

	if (enqueued == 0)
		return;


	for (i = 0; i < 2; ++i)
		reada_start_machine(fs_info);
}
