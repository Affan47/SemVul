i915_gem_init_stolen(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long reserved_total, reserved_base = 0, reserved_size;
	unsigned long stolen_top;

	mutex_init(&dev_priv->mm.stolen_lock);

#ifdef CONFIG_INTEL_IOMMU
	if (intel_iommu_gfx_mapped && INTEL_INFO(dev)->gen < 8) {
		DRM_INFO("DMAR active, disabling use of stolen memory\n");
		return 0;
	}
#endif

	if (dev_priv->gtt.stolen_size == 0)
		return 0;

	dev_priv->mm.stolen_base = i915_stolen_to_physical(dev);
	if (dev_priv->mm.stolen_base == 0)
		return 0;

	stolen_top = dev_priv->mm.stolen_base + dev_priv->gtt.stolen_size;

	switch (INTEL_INFO(dev_priv)->gen) {
	case 2:
	case 3:
		break;
	case 4:
		if (IS_G4X(dev))
			g4x_get_stolen_reserved(dev_priv, &reserved_base,
						&reserved_size);
		break;
	case 5:

		reserved_size = 1024 * 1024;
		reserved_base = stolen_top - reserved_size;
		break;
	case 6:
		gen6_get_stolen_reserved(dev_priv, &reserved_base,
					 &reserved_size);
		break;
	case 7:
		gen7_get_stolen_reserved(dev_priv, &reserved_base,
					 &reserved_size);
		break;
	default:
		if (IS_BROADWELL(dev_priv) || IS_SKYLAKE(dev_priv))
			bdw_get_stolen_reserved(dev_priv, &reserved_base,
						&reserved_size);
		else
			gen8_get_stolen_reserved(dev_priv, &reserved_base,
						 &reserved_size);
		break;
	}


	if (reserved_base == 0) {
		reserved_size = 0;
		reserved_base = stolen_top;
	}

	if (reserved_base < dev_priv->mm.stolen_base ||
	    reserved_base + reserved_size > stolen_top) {
		DRM_DEBUG_KMS("Stolen reserved area [0x%08lx - 0x%08lx] outside stolen memory [0x%08lx - 0x%08lx]\n",
			      reserved_base, reserved_base + reserved_size,
			      dev_priv->mm.stolen_base, stolen_top);
		return 0;
	}


	reserved_total = stolen_top - reserved_base;

	DRM_DEBUG_KMS("Memory reserved for graphics device: %zuK, usable: %luK\n",
		      dev_priv->gtt.stolen_size >> 10,
		      (dev_priv->gtt.stolen_size - reserved_total) >> 10);

	dev_priv->gtt.stolen_usable_size = dev_priv->gtt.stolen_size -
					   reserved_total;


	drm_mm_init(&dev_priv->mm.stolen, 0, dev_priv->gtt.stolen_usable_size);

	return 0;
}
