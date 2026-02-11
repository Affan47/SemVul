psb_gtt_roll(struct drm_device *dev, struct gtt_range *r, int roll)
{
	u32 __iomem *gtt_slot;
	u32 pte;
	int i;

	if (roll >= r->npage) {
		WARN_ON(1);
		return;
	}

	r->roll = roll;


	if (!r->stolen && !r->in_gart)
		return;

	gtt_slot = psb_gtt_entry(dev, r);

	for (i = r->roll; i < r->npage; i++) {
		pte = psb_gtt_mask_pte(page_to_pfn(r->pages[i]),
				       PSB_MMU_CACHED_MEMORY);
		iowrite32(pte, gtt_slot++);
	}
	for (i = 0; i < r->roll; i++) {
		pte = psb_gtt_mask_pte(page_to_pfn(r->pages[i]),
				       PSB_MMU_CACHED_MEMORY);
		iowrite32(pte, gtt_slot++);
	}
	ioread32(gtt_slot - 1);
}
