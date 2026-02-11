_targets(CMD_ARGS)
{
	int r = 0;
	struct dm_task *dmt;
	struct dm_versions *target;
	struct dm_versions *last_target;

	if (!(dmt = dm_task_create(DM_DEVICE_LIST_VERSIONS)))
		return 0;

	if (_switches[CHECKS_ARG] && !dm_task_enable_checks(dmt))
		goto out;

	if (!dm_task_run(dmt))
		goto out;

	target = dm_task_get_versions(dmt);


	do {
		last_target = target;

		printf("%-16s v%d.%d.%d\n", target->name, target->version[0],
		       target->version[1], target->version[2]);

		target = (struct dm_versions *)((char *) target + target->next);
	} while (last_target != target);

	r = 1;

      out:
	dm_task_destroy(dmt);
	return r;
}
