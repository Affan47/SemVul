__lookup_dm_origin(struct block_device *origin)
{
	struct list_head *ol;
	struct dm_origin *o;

	ol = &_dm_origins[origin_hash(origin)];
	list_for_each_entry (o, ol, hash_list)
		if (bdev_equal(o->dev->bdev, origin))
			return o;

	return NULL;
}
