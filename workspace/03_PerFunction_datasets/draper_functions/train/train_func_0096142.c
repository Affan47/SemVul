gen8_gmch_probe(struct drm_device *dev,
			   u64 *gtt_total,
			   size_t *stolen,
			   phys_addr_t *mappable_base,
			   u64 *mappable_end)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u64 gtt_size;
	u16 snb_gmch_ctl;
	int ret;


	*mappable_base = pci_resource_start(dev->pdev, 2);
	*mappable_end = pci_resource_len(dev->pdev, 2);

	if (!pci_set_dma_mask(dev->pdev, DMA_BIT_MASK(39)))
		pci_set_consistent_dma_mask(dev->pdev, DMA_BIT_MASK(39));

	pci_read_config_word(dev->pdev, SNB_GMCH_CTRL, &snb_gmch_ctl);

	if (INTEL_INFO(dev)->gen >= 9) {
		*stolen = gen9_get_stolen_size(snb_gmch_ctl);
		gtt_size = gen8_get_total_gtt_size(snb_gmch_ctl);
	} else if (IS_CHERRYVIEW(dev)) {
		*stolen = chv_get_stolen_size(snb_gmch_ctl);
		gtt_size = chv_get_total_gtt_size(snb_gmch_ctl);
	} else {
		*stolen = gen8_get_stolen_size(snb_gmch_ctl);
		gtt_size = gen8_get_total_gtt_size(snb_gmch_ctl);
	}

	*gtt_total = (gtt_size / sizeof(gen8_pte_t)) << PAGE_SHIFT;

	if (IS_CHERRYVIEW(dev) || IS_BROXTON(dev))
		chv_setup_private_ppat(dev_priv);
	else
		bdw_setup_private_ppat(dev_priv);

	ret = ggtt_probe_common(dev, gtt_size);

	dev_priv->gtt.base.clear_range = gen8_ggtt_clear_range;
	dev_priv->gtt.base.insert_entries = gen8_ggtt_insert_entries;
	dev_priv->gtt.base.bind_vma = ggtt_bind_vma;
	dev_priv->gtt.base.unbind_vma = ggtt_unbind_vma;

	return ret;
}
