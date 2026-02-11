dmi_sysfs_register_handle(const struct dmi_header *dh,
					     void *_ret)
{
	struct dmi_sysfs_entry *entry;
	int *ret = _ret;


	if (*ret)
		return;


	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		*ret = -ENOMEM;
		return;
	}


	memcpy(&entry->dh, dh, sizeof(*dh));
	entry->instance = instance_counts[dh->type]++;
	entry->position = position_count++;

	entry->kobj.kset = dmi_kset;
	*ret = kobject_init_and_add(&entry->kobj, &dmi_sysfs_entry_ktype, NULL,
				    "%d-%d", dh->type, entry->instance);

	if (*ret) {
		kfree(entry);
		return;
	}


	spin_lock(&entry_list_lock);
	list_add_tail(&entry->list, &entry_list);
	spin_unlock(&entry_list_lock);


	switch (dh->type) {
	case DMI_ENTRY_SYSTEM_EVENT_LOG:
		*ret = dmi_system_event_log(entry);
		break;
	default:

		break;
	}
	if (*ret)
		goto out_err;


	*ret = sysfs_create_bin_file(&entry->kobj, &dmi_entry_raw_attr);
	if (*ret)
		goto out_err;

	return;
out_err:
	kobject_put(entry->child);
	kobject_put(&entry->kobj);
	return;
}
