__i915_printk(struct drm_i915_private *dev_priv, const char *level,
	      const char *fmt, ...)
{
	static bool shown_bug_once;
	struct device *dev = dev_priv->dev->dev;
	bool is_error = level[1] <= KERN_ERR[1];
	bool is_debug = level[1] == KERN_DEBUG[1];
	struct va_format vaf;
	va_list args;

	if (is_debug && !(drm_debug & DRM_UT_DRIVER))
		return;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	dev_printk(level, dev, "[" DRM_NAME ":%ps] %pV",
		   __builtin_return_address(0), &vaf);

	if (is_error && !shown_bug_once) {
		dev_notice(dev, "%s", FDO_BUG_MSG);
		shown_bug_once = true;
	}

	va_end(args);
}
