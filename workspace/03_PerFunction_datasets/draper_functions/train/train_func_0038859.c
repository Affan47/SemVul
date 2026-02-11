gen6_ggtt_insert_entries(struct i915_address_space *vm,
				     struct sg_table *st,
				     uint64_t start,
				     enum i915_cache_level level, u32 flags)
{
	struct drm_i915_private *dev_priv = to_i915(vm->dev);
	struct i915_ggtt *ggtt = &dev_priv->ggtt;
	unsigned first_entry = start >> PAGE_SHIFT;
	gen6_pte_t __iomem *gtt_entries =
		(gen6_pte_t __iomem *)ggtt->gsm + first_entry;
	int i = 0;
	struct sg_page_iter sg_iter;
	dma_addr_t addr = 0;
	int rpm_atomic_seq;

	rpm_atomic_seq = assert_rpm_atomic_begin(dev_priv);

	for_each_sg_page(st->sgl, &sg_iter, st->nents, 0) {
		addr = sg_page_iter_dma_address(&sg_iter);
		iowrite32(vm->pte_encode(addr, level, true, flags), &gtt_entries[i]);
		i++;
	}


	if (i != 0) {
		unsigned long gtt = readl(&gtt_entries[i-1]);
		WARN_ON(gtt != vm->pte_encode(addr, level, true, flags));
	}


	I915_WRITE(GFX_FLSH_CNTL_GEN6, GFX_FLSH_CNTL_EN);
	POSTING_READ(GFX_FLSH_CNTL_GEN6);

	assert_rpm_atomic_end(dev_priv, rpm_atomic_seq);
}
