lazy_bitmap_update_due(struct drbd_device *device)
{
	return time_after(jiffies, device->rs_last_bcast + 2*HZ);
}
