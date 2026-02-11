intel_uncore_forcewake_for_write(struct drm_i915_private *dev_priv,
				 i915_reg_t reg)
{
	enum forcewake_domains fw_domains;

	if (intel_vgpu_active(dev_priv->dev))
		return 0;

	switch (INTEL_INFO(dev_priv)->gen) {
	case 9:
		fw_domains = __gen9_reg_write_fw_domains(i915_mmio_reg_offset(reg));
		break;
	case 8:
		if (IS_CHERRYVIEW(dev_priv))
			fw_domains = __chv_reg_write_fw_domains(i915_mmio_reg_offset(reg));
		else
			fw_domains = __gen8_reg_write_fw_domains(i915_mmio_reg_offset(reg));
		break;
	case 7:
	case 6:
		fw_domains = FORCEWAKE_RENDER;
		break;
	default:
		MISSING_CASE(INTEL_INFO(dev_priv)->gen);
	case 5:
	case 4:
	case 3:
	case 2:
		return 0;
	}

	WARN_ON(fw_domains & ~dev_priv->uncore.fw_domains);

	return fw_domains;
}
