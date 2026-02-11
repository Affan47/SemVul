dev_wait(struct dm_ioctl *param, size_t param_size)
{
	int r = 0;
	struct mapped_device *md;
	struct dm_table *table;
	int srcu_idx;

	md = find_device(param);
	if (!md)
		return -ENXIO;


	if (dm_wait_event(md, param->event_nr)) {
		r = -ERESTARTSYS;
		goto out;
	}


	__dev_status(md, param);

	table = dm_get_live_or_inactive_table(md, param, &srcu_idx);
	if (table)
		retrieve_status(table, param, param_size);
	dm_put_live_table(md, srcu_idx);

out:
	dm_put(md);

	return r;
}
