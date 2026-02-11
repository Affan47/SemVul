regmap_cache_only_write_file(struct file *file,
					    const char __user *user_buf,
					    size_t count, loff_t *ppos)
{
	struct regmap *map = container_of(file->private_data,
					  struct regmap, cache_only);
	ssize_t result;
	bool was_enabled, require_sync = false;
	int err;

	map->lock(map->lock_arg);

	was_enabled = map->cache_only;

	result = debugfs_write_file_bool(file, user_buf, count, ppos);
	if (result < 0) {
		map->unlock(map->lock_arg);
		return result;
	}

	if (map->cache_only && !was_enabled) {
		dev_warn(map->dev, "debugfs cache_only=Y forced\n");
		add_taint(TAINT_USER, LOCKDEP_STILL_OK);
	} else if (!map->cache_only && was_enabled) {
		dev_warn(map->dev, "debugfs cache_only=N forced: syncing cache\n");
		require_sync = true;
	}

	map->unlock(map->lock_arg);

	if (require_sync) {
		err = regcache_sync(map);
		if (err)
			dev_err(map->dev, "Failed to sync cache %d\n", err);
	}

	return result;
}
