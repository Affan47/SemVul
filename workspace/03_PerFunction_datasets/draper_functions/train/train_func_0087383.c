init_vbt_defaults(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	enum port port;

	dev_priv->vbt.crt_ddc_pin = GMBUS_PIN_VGADDC;


	dev_priv->vbt.backlight.present = true;


	dev_priv->vbt.lvds_dither = 1;
	dev_priv->vbt.lvds_vbt = 0;


	dev_priv->vbt.sdvo_lvds_vbt_mode = NULL;


	dev_priv->vbt.int_tv_support = 1;
	dev_priv->vbt.int_crt_support = 1;


	dev_priv->vbt.lvds_use_ssc = 1;


	dev_priv->vbt.lvds_ssc_freq = intel_bios_ssc_frequency(dev,
			!HAS_PCH_SPLIT(dev));
	DRM_DEBUG_KMS("Set default to SSC at %d kHz\n", dev_priv->vbt.lvds_ssc_freq);

	for (port = PORT_A; port < I915_MAX_PORTS; port++) {
		struct ddi_vbt_port_info *info =
			&dev_priv->vbt.ddi_port_info[port];

		info->hdmi_level_shift = HDMI_LEVEL_SHIFT_UNKNOWN;

		info->supports_dvi = (port != PORT_A && port != PORT_E);
		info->supports_hdmi = info->supports_dvi;
		info->supports_dp = (port != PORT_E);
	}
}
