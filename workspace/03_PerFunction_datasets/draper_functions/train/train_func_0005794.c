get_gmbus_pin(struct drm_i915_private *dev_priv,
					     unsigned int pin)
{
	if (IS_BROXTON(dev_priv))
		return &gmbus_pins_bxt[pin];
	else if (IS_SKYLAKE(dev_priv) || IS_KABYLAKE(dev_priv))
		return &gmbus_pins_skl[pin];
	else if (IS_BROADWELL(dev_priv))
		return &gmbus_pins_bdw[pin];
	else
		return &gmbus_pins[pin];
}
