bdw_get_stolen_reserved(struct drm_i915_private *dev_priv,
				    unsigned long *base, unsigned long *size)
{
	uint32_t reg_val = I915_READ(GEN6_STOLEN_RESERVED);
	unsigned long stolen_top;

	stolen_top = dev_priv->mm.stolen_base + dev_priv->gtt.stolen_size;

	*base = reg_val & GEN6_STOLEN_RESERVED_ADDR_MASK;


	if (*base == 0)
		*size = 0;
	else
		*size = stolen_top - *base;
}
