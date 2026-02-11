drbd_may_do_local_read(struct drbd_device *device, sector_t sector, int size)
{
	unsigned long sbnr, ebnr;
	sector_t esector, nr_sectors;

	if (device->state.disk == D_UP_TO_DATE)
		return true;
	if (device->state.disk != D_INCONSISTENT)
		return false;
	esector = sector + (size >> 9) - 1;
	nr_sectors = drbd_get_capacity(device->this_bdev);
	D_ASSERT(device, sector  < nr_sectors);
	D_ASSERT(device, esector < nr_sectors);

	sbnr = BM_SECT_TO_BIT(sector);
	ebnr = BM_SECT_TO_BIT(esector);

	return drbd_bm_count_bits(device, sbnr, ebnr) == 0;
}
