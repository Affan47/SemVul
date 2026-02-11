lba_is_aligned(struct fdisk_context *cxt, uintmax_t lba)
{
	unsigned long granularity = max(cxt->phy_sector_size, cxt->min_io_size);
	uintmax_t offset;

	if (cxt->grain > granularity)
		granularity = cxt->grain;

	offset = (lba * cxt->sector_size) % granularity;

	return !((granularity + cxt->alignment_offset - offset) % granularity);
}
