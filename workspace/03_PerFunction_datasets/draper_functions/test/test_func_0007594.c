i915_runtime_pm_status(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = m->private;
	struct drm_device *dev = node->minor->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!HAS_RUNTIME_PM(dev)) {
		seq_puts(m, "not supported\n");
		return 0;
	}

	seq_printf(m, "GPU idle: %s\n", yesno(!dev_priv->mm.busy));
	seq_printf(m, "IRQs disabled: %s\n",
		   yesno(!intel_irqs_enabled(dev_priv)));
#ifdef CONFIG_PM
	seq_printf(m, "Usage count: %d\n",
		   atomic_read(&dev->dev->power.usage_count));
#else
	seq_printf(m, "Device Power Management (CONFIG_PM) disabled\n");
#endif

	return 0;
}
