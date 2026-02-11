_deps(struct dm_task **dmt, struct dm_pool *mem, uint32_t major, uint32_t minor,
		 const char **name, const char **uuid, unsigned inactive_table,
		 struct dm_info *info, struct dm_deps **deps)
{
	memset(info, 0, sizeof(*info));

	if (!dm_is_dm_major(major)) {
		if (name)
			*name = "";
		if (uuid)
			*uuid = "";
		*deps = NULL;
		info->major = major;
		info->minor = minor;
		return 1;
	}

	if (!(*dmt = dm_task_create(DM_DEVICE_DEPS))) {
		log_error("deps dm_task creation failed");
		return 0;
	}

	if (!dm_task_set_major(*dmt, major)) {
		log_error("_deps: failed to set major for (%" PRIu32 ":%" PRIu32 ")",
			  major, minor);
		goto failed;
	}

	if (!dm_task_set_minor(*dmt, minor)) {
		log_error("_deps: failed to set minor for (%" PRIu32 ":%" PRIu32 ")",
			  major, minor);
		goto failed;
	}

	if (inactive_table && !dm_task_query_inactive_table(*dmt)) {
		log_error("_deps: failed to set inactive table for (%" PRIu32 ":%" PRIu32 ")",
			  major, minor);
		goto failed;
	}

	if (!dm_task_run(*dmt)) {
		log_error("_deps: task run failed for (%" PRIu32 ":%" PRIu32 ")",
			  major, minor);
		goto failed;
	}

	if (!dm_task_get_info(*dmt, info)) {
		log_error("_deps: failed to get info for (%" PRIu32 ":%" PRIu32 ")",
			  major, minor);
		goto failed;
	}

	if (!info->exists) {
		if (name)
			*name = "";
		if (uuid)
			*uuid = "";
		*deps = NULL;
	} else {
		if (info->major != major) {
			log_error("Inconsistent dtree major number: %u != %u",
				  major, info->major);
			goto failed;
		}
		if (info->minor != minor) {
			log_error("Inconsistent dtree minor number: %u != %u",
				  minor, info->minor);
			goto failed;
		}
		if (name && !(*name = dm_pool_strdup(mem, dm_task_get_name(*dmt)))) {
			log_error("name pool_strdup failed");
			goto failed;
		}
		if (uuid && !(*uuid = dm_pool_strdup(mem, dm_task_get_uuid(*dmt)))) {
			log_error("uuid pool_strdup failed");
			goto failed;
		}
		*deps = dm_task_get_deps(*dmt);
	}

	return 1;

failed:
	dm_task_destroy(*dmt);
	return 0;
}
