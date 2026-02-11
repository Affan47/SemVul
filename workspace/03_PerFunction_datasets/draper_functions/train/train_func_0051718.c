mlx5_mr_cache_cleanup(struct mlx5_ib_dev *dev)
{
	int i;

	dev->cache.stopped = 1;
	flush_workqueue(dev->cache.wq);

	mlx5_mr_cache_debugfs_cleanup(dev);

	for (i = 0; i < MAX_MR_CACHE_ENTRIES; i++)
		clean_keys(dev, i);

	destroy_workqueue(dev->cache.wq);
	wait_for_async_commands(dev);
	del_timer_sync(&dev->delay_timer);

	return 0;
}
