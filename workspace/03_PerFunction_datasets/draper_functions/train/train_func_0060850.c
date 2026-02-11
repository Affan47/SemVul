snapshot_iterate_devices(struct dm_target *ti,
				    iterate_devices_callout_fn fn, void *data)
{
	struct dm_snapshot *snap = ti->private;
	int r;

	r = fn(ti, snap->origin, 0, ti->len, data);

	if (!r)
		r = fn(ti, snap->cow, 0, get_dev_size(snap->cow->bdev), data);

	return r;
}
