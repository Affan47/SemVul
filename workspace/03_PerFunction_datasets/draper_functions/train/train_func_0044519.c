psb_do_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct psb_gtt *pg = &dev_priv->gtt;

	uint32_t stolen_gtt;

	if (pg->mmu_gatt_start & 0x0FFFFFFF) {
		dev_err(dev->dev, "Gatt must be 256M aligned. This is a bug.\n");
		return -EINVAL;
	}

	stolen_gtt = (pg->stolen_size >> PAGE_SHIFT) * 4;
	stolen_gtt = (stolen_gtt + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stolen_gtt = (stolen_gtt < pg->gtt_pages) ? stolen_gtt : pg->gtt_pages;

	dev_priv->gatt_free_offset = pg->mmu_gatt_start +
	    (stolen_gtt << PAGE_SHIFT) * 1024;

	spin_lock_init(&dev_priv->irqmask_lock);
	spin_lock_init(&dev_priv->lock_2d);

	PSB_WSGX32(0x00000000, PSB_CR_BIF_BANK0);
	PSB_WSGX32(0x00000000, PSB_CR_BIF_BANK1);
	PSB_RSGX32(PSB_CR_BIF_BANK1);


	PSB_WSGX32((PSB_RSGX32(PSB_CR_BIF_CTRL) & ~_PSB_MMU_ER_MASK),
		   PSB_CR_BIF_CTRL);
	PSB_RSGX32(PSB_CR_BIF_CTRL);

	psb_spank(dev_priv);


	PSB_WSGX32(pg->gatt_start, PSB_CR_BIF_TWOD_REQ_BASE);
	PSB_RSGX32(PSB_CR_BIF_TWOD_REQ_BASE);

	return 0;
}
