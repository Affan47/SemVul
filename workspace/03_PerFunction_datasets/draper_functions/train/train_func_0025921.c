_dev_cache_seek_devt(dev_t dev)
{
	struct device *d = NULL;
	struct dm_hash_node *n = dm_hash_get_first(_cache.names);
	while (n) {
		d = dm_hash_get_data(_cache.names, n);
		if (d->dev == dev)
			return d;
		n = dm_hash_get_next(_cache.names, n);
	}
	return NULL;
}
