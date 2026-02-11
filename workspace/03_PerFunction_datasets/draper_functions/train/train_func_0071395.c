i915_fbc_status(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = m->private;
	struct drm_device *dev = node->minor->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!HAS_FBC(dev)) {
		seq_puts(m, "FBC unsupported on this chipset\n");
		return 0;
	}

	intel_runtime_pm_get(dev_priv);
	mutex_lock(&dev_priv->fbc.lock);

	if (intel_fbc_enabled(dev_priv))
		seq_puts(m, "FBC enabled\n");
	else
		seq_printf(m, "FBC disabled: %s\n",
			  intel_no_fbc_reason_str(dev_priv->fbc.no_fbc_reason));

	if (INTEL_INFO(dev_priv)->gen >= 7)
		seq_printf(m, "Compressing: %s\n",
			   yesno(I915_READ(FBC_STATUS2) &
				 FBC_COMPRESSION_MASK));

	mutex_unlock(&dev_priv->fbc.lock);
	intel_runtime_pm_put(dev_priv);

	return 0;
}
