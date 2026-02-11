check_sorted(int ring_id,
			 const struct drm_i915_reg_descriptor *reg_table,
			 int reg_count)
{
	int i;
	u32 previous = 0;
	bool ret = true;

	for (i = 0; i < reg_count; i++) {
		u32 curr = i915_mmio_reg_offset(reg_table[i].addr);

		if (curr < previous) {
			DRM_ERROR("CMD: table not sorted ring=%d entry=%d reg=0x%08X prev=0x%08X\n",
				  ring_id, i, curr, previous);
			ret = false;
		}

		previous = curr;
	}

	return ret;
}
