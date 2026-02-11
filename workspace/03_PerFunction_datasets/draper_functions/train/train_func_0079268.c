i915_save_state(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int i;

	mutex_lock(&dev->struct_mutex);

	i915_save_display(dev);

	if (IS_GEN4(dev))
		pci_read_config_word(dev->pdev, GCDGMBUS,
				     &dev_priv->regfile.saveGCDGMBUS);


	if (INTEL_INFO(dev)->gen < 7)
		dev_priv->regfile.saveCACHE_MODE_0 = I915_READ(CACHE_MODE_0);


	dev_priv->regfile.saveMI_ARB_STATE = I915_READ(MI_ARB_STATE);


	if (IS_GEN2(dev_priv) && IS_MOBILE(dev_priv)) {
		for (i = 0; i < 7; i++) {
			dev_priv->regfile.saveSWF0[i] = I915_READ(SWF0(i));
			dev_priv->regfile.saveSWF1[i] = I915_READ(SWF1(i));
		}
		for (i = 0; i < 3; i++)
			dev_priv->regfile.saveSWF3[i] = I915_READ(SWF3(i));
	} else if (IS_GEN2(dev_priv)) {
		for (i = 0; i < 7; i++)
			dev_priv->regfile.saveSWF1[i] = I915_READ(SWF1(i));
	} else if (HAS_GMCH_DISPLAY(dev_priv)) {
		for (i = 0; i < 16; i++) {
			dev_priv->regfile.saveSWF0[i] = I915_READ(SWF0(i));
			dev_priv->regfile.saveSWF1[i] = I915_READ(SWF1(i));
		}
		for (i = 0; i < 3; i++)
			dev_priv->regfile.saveSWF3[i] = I915_READ(SWF3(i));
	}

	mutex_unlock(&dev->struct_mutex);

	return 0;
}
