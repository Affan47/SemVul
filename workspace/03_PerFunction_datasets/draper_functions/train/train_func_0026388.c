_scsih_raid_device_find_by_wwid(struct MPT3SAS_ADAPTER *ioc, u64 wwid)
{
	struct _raid_device *raid_device, *r;

	r = NULL;
	list_for_each_entry(raid_device, &ioc->raid_device_list, list) {
		if (raid_device->wwid != wwid)
			continue;
		r = raid_device;
		goto out;
	}

 out:
	return r;
}
