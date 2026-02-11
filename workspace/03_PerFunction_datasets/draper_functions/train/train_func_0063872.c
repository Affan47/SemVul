gen6_scratch_va_range(struct i915_hw_ppgtt *ppgtt,
				  uint64_t start, uint64_t length)
{
	struct i915_page_table *unused;
	uint32_t pde, temp;

	gen6_for_each_pde(unused, &ppgtt->pd, start, length, temp, pde)
		ppgtt->pd.page_table[pde] = ppgtt->base.scratch_pt;
}
