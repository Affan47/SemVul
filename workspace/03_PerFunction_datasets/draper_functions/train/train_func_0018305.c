intel_uncore_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	i915_check_vgpu(dev);

	intel_uncore_edram_detect(dev_priv);
	intel_uncore_fw_domains_init(dev);
	__intel_uncore_early_sanitize(dev, false);

	dev_priv->uncore.unclaimed_mmio_check = 1;

	switch (INTEL_INFO(dev)->gen) {
	default:
	case 9:
		ASSIGN_WRITE_MMIO_VFUNCS(gen9);
		ASSIGN_READ_MMIO_VFUNCS(gen9);
		break;
	case 8:
		if (IS_CHERRYVIEW(dev)) {
			ASSIGN_WRITE_MMIO_VFUNCS(chv);
			ASSIGN_READ_MMIO_VFUNCS(chv);

		} else {
			ASSIGN_WRITE_MMIO_VFUNCS(gen8);
			ASSIGN_READ_MMIO_VFUNCS(gen6);
		}
		break;
	case 7:
	case 6:
		if (IS_HASWELL(dev)) {
			ASSIGN_WRITE_MMIO_VFUNCS(hsw);
		} else {
			ASSIGN_WRITE_MMIO_VFUNCS(gen6);
		}

		if (IS_VALLEYVIEW(dev)) {
			ASSIGN_READ_MMIO_VFUNCS(vlv);
		} else {
			ASSIGN_READ_MMIO_VFUNCS(gen6);
		}
		break;
	case 5:
		ASSIGN_WRITE_MMIO_VFUNCS(gen5);
		ASSIGN_READ_MMIO_VFUNCS(gen5);
		break;
	case 4:
	case 3:
	case 2:
		ASSIGN_WRITE_MMIO_VFUNCS(gen2);
		ASSIGN_READ_MMIO_VFUNCS(gen2);
		break;
	}

	if (intel_vgpu_active(dev)) {
		ASSIGN_WRITE_MMIO_VFUNCS(vgpu);
		ASSIGN_READ_MMIO_VFUNCS(vgpu);
	}

	i915_check_and_clear_faults(dev);
}
