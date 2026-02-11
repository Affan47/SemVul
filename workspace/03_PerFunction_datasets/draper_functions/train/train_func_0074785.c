gen8_alloc_va_range_3lvl(struct i915_address_space *vm,
				    struct i915_page_directory_pointer *pdp,
				    uint64_t start,
				    uint64_t length)
{
	struct i915_hw_ppgtt *ppgtt =
		container_of(vm, struct i915_hw_ppgtt, base);
	unsigned long *new_page_dirs, *new_page_tables;
	struct drm_device *dev = vm->dev;
	struct i915_page_directory *pd;
	const uint64_t orig_start = start;
	const uint64_t orig_length = length;
	uint64_t temp;
	uint32_t pdpe;
	uint32_t pdpes = I915_PDPES_PER_PDP(dev);
	int ret;


	if (WARN_ON(start + length < start))
		return -ENODEV;

	if (WARN_ON(start + length > vm->total))
		return -ENODEV;

	ret = alloc_gen8_temp_bitmaps(&new_page_dirs, &new_page_tables, pdpes);
	if (ret)
		return ret;


	ret = gen8_ppgtt_alloc_page_directories(vm, pdp, start, length,
						new_page_dirs);
	if (ret) {
		free_gen8_temp_bitmaps(new_page_dirs, new_page_tables);
		return ret;
	}


	gen8_for_each_pdpe(pd, pdp, start, length, temp, pdpe) {
		ret = gen8_ppgtt_alloc_pagetabs(vm, pd, start, length,
						new_page_tables + pdpe * BITS_TO_LONGS(I915_PDES));
		if (ret)
			goto err_out;
	}

	start = orig_start;
	length = orig_length;


	gen8_for_each_pdpe(pd, pdp, start, length, temp, pdpe) {
		gen8_pde_t *const page_directory = kmap_px(pd);
		struct i915_page_table *pt;
		uint64_t pd_len = length;
		uint64_t pd_start = start;
		uint32_t pde;


		WARN_ON(!pd);

		gen8_for_each_pde(pt, pd, pd_start, pd_len, temp, pde) {

			WARN_ON(!pt);
			WARN_ON(!pd_len);
			WARN_ON(!gen8_pte_count(pd_start, pd_len));


			bitmap_set(pt->used_ptes,
				   gen8_pte_index(pd_start),
				   gen8_pte_count(pd_start, pd_len));


			__set_bit(pde, pd->used_pdes);


			page_directory[pde] = gen8_pde_encode(px_dma(pt),
							      I915_CACHE_LLC);
			trace_i915_page_table_entry_map(&ppgtt->base, pde, pt,
							gen8_pte_index(start),
							gen8_pte_count(start, length),
							GEN8_PTES);


		}

		kunmap_px(ppgtt, page_directory);
		__set_bit(pdpe, pdp->used_pdpes);
		gen8_setup_page_directory(ppgtt, pdp, pd, pdpe);
	}

	free_gen8_temp_bitmaps(new_page_dirs, new_page_tables);
	mark_tlbs_dirty(ppgtt);
	return 0;

err_out:
	while (pdpe--) {
		for_each_set_bit(temp, new_page_tables + pdpe *
				BITS_TO_LONGS(I915_PDES), I915_PDES)
			free_pt(dev, pdp->page_directory[pdpe]->page_table[temp]);
	}

	for_each_set_bit(pdpe, new_page_dirs, pdpes)
		free_pd(dev, pdp->page_directory[pdpe]);

	free_gen8_temp_bitmaps(new_page_dirs, new_page_tables);
	mark_tlbs_dirty(ppgtt);
	return ret;
}
