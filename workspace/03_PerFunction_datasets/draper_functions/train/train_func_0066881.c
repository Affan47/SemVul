_get_device_size(const char *name)
{
	uint64_t start, length, size = UINT64_C(0);
	struct dm_info info;
	char *target_type, *params;
	struct dm_task *dmt;
	void *next = NULL;

	if (!(dmt = dm_task_create(DM_DEVICE_TABLE)))
		return 0;

	if (!_set_task_device(dmt, name, 0))
		goto out;

	if (_switches[NOOPENCOUNT_ARG] && !dm_task_no_open_count(dmt))
		goto out;

	if (_switches[INACTIVE_ARG] && !dm_task_query_inactive_table(dmt))
		goto out;

	if (_switches[CHECKS_ARG] && !dm_task_enable_checks(dmt))
		goto out;

	if (!dm_task_run(dmt))
		goto out;

	if (!dm_task_get_info(dmt, &info) || !info.exists)
		goto out;

	do {
		next = dm_get_next_target(dmt, next, &start, &length,
					  &target_type, &params);
		size += length;
	} while (next);

      out:
	dm_task_destroy(dmt);
	return size;
}
