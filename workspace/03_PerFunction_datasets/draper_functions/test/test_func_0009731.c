gen5_assert_iir_is_zero(struct drm_i915_private *dev_priv, u32 reg)
{
	u32 val = I915_READ(reg);

	if (val == 0)
		return;

	WARN(1, "Interrupt register 0x%x is not zero: 0x%08x\n",
	     reg, val);
	I915_WRITE(reg, 0xffffffff);
	POSTING_READ(reg);
	I915_WRITE(reg, 0xffffffff);
	POSTING_READ(reg);
}
