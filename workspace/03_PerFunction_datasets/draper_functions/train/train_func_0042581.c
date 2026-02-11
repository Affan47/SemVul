gen6_gmch_probe(struct i915_ggtt *ggtt)
{
	struct drm_device *dev = ggtt->base.dev;
	u16 snb_gmch_ctl;
	int ret;

	ggtt->mappable_base = pci_resource_start(dev->pdev, 2);
	ggtt->mappable_end = pci_resource_len(dev->pdev, 2);


	if ((ggtt->mappable_end < (64<<20) || (ggtt->mappable_end > (512<<20)))) {
		DRM_ERROR("Unknown GMADR size (%llx)\n", ggtt->mappable_end);
		return -ENXIO;
	}

	if (!pci_set_dma_mask(dev->pdev, DMA_BIT_MASK(40)))
		pci_set_consistent_dma_mask(dev->pdev, DMA_BIT_MASK(40));
	pci_read_config_word(dev->pdev, SNB_GMCH_CTRL, &snb_gmch_ctl);

	ggtt->stolen_size = gen6_get_stolen_size(snb_gmch_ctl);
	ggtt->size = gen6_get_total_gtt_size(snb_gmch_ctl);
	ggtt->base.total = (ggtt->size / sizeof(gen6_pte_t)) << PAGE_SHIFT;

	ret = ggtt_probe_common(dev, ggtt->size);

	ggtt->base.clear_range = gen6_ggtt_clear_range;
	ggtt->base.insert_entries = gen6_ggtt_insert_entries;
	ggtt->base.bind_vma = ggtt_bind_vma;
	ggtt->base.unbind_vma = ggtt_unbind_vma;

	return ret;
}
