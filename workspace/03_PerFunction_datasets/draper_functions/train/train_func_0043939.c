btrfs_alloc_subvolume_writers(void)
{
	struct btrfs_subvolume_writers *writers;
	int ret;

	writers = kmalloc(sizeof(*writers), GFP_NOFS);
	if (!writers)
		return ERR_PTR(-ENOMEM);

	ret = percpu_counter_init(&writers->counter, 0, GFP_KERNEL);
	if (ret < 0) {
		kfree(writers);
		return ERR_PTR(ret);
	}

	init_waitqueue_head(&writers->wait);
	return writers;
}
