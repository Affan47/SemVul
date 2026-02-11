_do_rename(const char *name, const char *new_name, const char *new_uuid) {
	int r = 0;
	struct dm_task *dmt;
	uint32_t cookie = 0;
	uint16_t udev_flags = 0;

	if (!(dmt = dm_task_create(DM_DEVICE_RENAME)))
		return 0;


	if (!_set_task_device(dmt, name, 0))
		goto out;

	if (new_uuid) {
		if (!dm_task_set_newuuid(dmt, new_uuid))
			goto out;
	} else if (!new_name || !dm_task_set_newname(dmt, new_name))
		goto out;

	if (_switches[NOOPENCOUNT_ARG] && !dm_task_no_open_count(dmt))
		goto out;

	if (_switches[INACTIVE_ARG] && !dm_task_query_inactive_table(dmt))
		goto out;

	if (_switches[CHECKS_ARG] && !dm_task_enable_checks(dmt))
		goto out;

	if (_switches[NOUDEVRULES_ARG])
		udev_flags |= DM_UDEV_DISABLE_DM_RULES_FLAG |
			      DM_UDEV_DISABLE_SUBSYSTEM_RULES_FLAG;

	if (_udev_cookie)
		cookie = _udev_cookie;

	if (_udev_only)
		udev_flags |= DM_UDEV_DISABLE_LIBRARY_FALLBACK;

	if (!dm_task_set_cookie(dmt, &cookie, udev_flags) ||
	    !dm_task_run(dmt))
		goto out;

	r = 1;

      out:
	if (!_udev_cookie)
		(void) dm_udev_wait(cookie);

	dm_task_destroy(dmt);

	return r;
}
