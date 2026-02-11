gen6_alloc_va_range(struct i915_address_space *vm,
			       uint64_t start_in, uint64_t length_in)
{
	DECLARE_BITMAP(new_page_tables, I915_PDES);
	struct drm_device *dev = vm->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_hw_ppgtt *ppgtt =
				container_of(vm, struct i915_hw_ppgtt, base);
	struct i915_page_table *pt;
	uint32_t start, length, start_save, length_save;
	uint32_t pde, temp;
	int ret;

	if (WARN_ON(start_in + length_in > ppgtt->base.total))
		return -ENODEV;

	start = start_save = start_in;
	length = length_save = length_in;

	bitmap_zero(new_page_tables, I915_PDES);


	gen6_for_each_pde(pt, &ppgtt->pd, start, length, temp, pde) {
		if (pt != vm->scratch_pt) {
			WARN_ON(bitmap_empty(pt->used_ptes, GEN6_PTES));
			continue;
		}


		WARN_ON(!bitmap_empty(pt->used_ptes, GEN6_PTES));

		pt = alloc_pt(dev);
		if (IS_ERR(pt)) {
			ret = PTR_ERR(pt);
			goto unwind_out;
		}

		gen6_initialize_pt(vm, pt);

		ppgtt->pd.page_table[pde] = pt;
		__set_bit(pde, new_page_tables);
		trace_i915_page_table_entry_alloc(vm, pde, start, GEN6_PDE_SHIFT);
	}

	start = start_save;
	length = length_save;

	gen6_for_each_pde(pt, &ppgtt->pd, start, length, temp, pde) {
		DECLARE_BITMAP(tmp_bitmap, GEN6_PTES);

		bitmap_zero(tmp_bitmap, GEN6_PTES);
		bitmap_set(tmp_bitmap, gen6_pte_index(start),
			   gen6_pte_count(start, length));

		if (__test_and_clear_bit(pde, new_page_tables))
			gen6_write_pde(&ppgtt->pd, pde, pt);

		trace_i915_page_table_entry_map(vm, pde, pt,
					 gen6_pte_index(start),
					 gen6_pte_count(start, length),
					 GEN6_PTES);
		bitmap_or(pt->used_ptes, tmp_bitmap, pt->used_ptes,
				GEN6_PTES);
	}

	WARN_ON(!bitmap_empty(new_page_tables, I915_PDES));


	readl(dev_priv->gtt.gsm);

	mark_tlbs_dirty(ppgtt);
	return 0;

unwind_out:
	for_each_set_bit(pde, new_page_tables, I915_PDES) {
		struct i915_page_table *pt = ppgtt->pd.page_table[pde];

		ppgtt->pd.page_table[pde] = vm->scratch_pt;
		free_pt(vm->dev, pt);
	}

	mark_tlbs_dirty(ppgtt);
	return ret;
}
