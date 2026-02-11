hpt370_filter(struct ata_device *adev, unsigned long mask)
{
	if (adev->class == ATA_DEV_ATA) {
		if (hpt_dma_blacklisted(adev, "UDMA", bad_ata33))
			mask &= ~ATA_MASK_UDMA;
		if (hpt_dma_blacklisted(adev, "UDMA100", bad_ata100_5))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	}
	return mask;
}
