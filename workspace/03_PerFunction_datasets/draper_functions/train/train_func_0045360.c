exofs_sysfs_sb_add(struct exofs_sb_info *sbi,
		       struct exofs_dt_device_info *dt_dev)
{
	struct kobject *s_kobj;
	int retval = 0;
	uint64_t pid = sbi->one_comp.obj.partition;


	s_kobj = &sbi->s_kobj;
	s_kobj->kset = exofs_kset;
	retval = kobject_init_and_add(s_kobj, &uuid_ktype,
			&exofs_kset->kobj,  "%s_%llx", dt_dev->osdname, pid);
	if (retval) {
		EXOFS_ERR("ERROR: Failed to create sysfs entry for "
			  "uuid-%s_%llx => %d\n", dt_dev->osdname, pid, retval);
		return -ENOMEM;
	}
	return 0;
}
