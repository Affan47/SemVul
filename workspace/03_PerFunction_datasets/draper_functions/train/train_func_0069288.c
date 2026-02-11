drbd_uuid_new_current(struct drbd_device *device) __must_hold(local)
{
	u64 val;
	unsigned long long bm_uuid;

	get_random_bytes(&val, sizeof(u64));

	spin_lock_irq(&device->ldev->md.uuid_lock);
	bm_uuid = device->ldev->md.uuid[UI_BITMAP];

	if (bm_uuid)
		drbd_warn(device, "bm UUID was already set: %llX\n", bm_uuid);

	device->ldev->md.uuid[UI_BITMAP] = device->ldev->md.uuid[UI_CURRENT];
	__drbd_uuid_set(device, UI_CURRENT, val);
	spin_unlock_irq(&device->ldev->md.uuid_lock);

	drbd_print_uuids(device, "new current UUID");

	drbd_md_sync(device);
}
