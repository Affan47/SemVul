oaktrail_lvds_get_configuration_mode(struct drm_device *dev,
					struct psb_intel_mode_device *mode_dev)
{
	struct drm_display_mode *mode = NULL;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_timing_info *ti = &dev_priv->gct_data.DTD;

	mode_dev->panel_fixed_mode = NULL;


	if (dev_priv->has_gct) {
		mode = kzalloc(sizeof(*mode), GFP_KERNEL);
		if (!mode)
			return;

		mode->hdisplay = (ti->hactive_hi << 8) | ti->hactive_lo;
		mode->vdisplay = (ti->vactive_hi << 8) | ti->vactive_lo;
		mode->hsync_start = mode->hdisplay + \
				((ti->hsync_offset_hi << 8) | \
				ti->hsync_offset_lo);
		mode->hsync_end = mode->hsync_start + \
				((ti->hsync_pulse_width_hi << 8) | \
				ti->hsync_pulse_width_lo);
		mode->htotal = mode->hdisplay + ((ti->hblank_hi << 8) | \
							ti->hblank_lo);
		mode->vsync_start = \
			mode->vdisplay + ((ti->vsync_offset_hi << 4) | \
						ti->vsync_offset_lo);
		mode->vsync_end = \
			mode->vsync_start + ((ti->vsync_pulse_width_hi << 4) | \
						ti->vsync_pulse_width_lo);
		mode->vtotal = mode->vdisplay + \
				((ti->vblank_hi << 8) | ti->vblank_lo);
		mode->clock = ti->pixel_clock * 10;
#if 0
		printk(KERN_INFO "hdisplay is %d\n", mode->hdisplay);
		printk(KERN_INFO "vdisplay is %d\n", mode->vdisplay);
		printk(KERN_INFO "HSS is %d\n", mode->hsync_start);
		printk(KERN_INFO "HSE is %d\n", mode->hsync_end);
		printk(KERN_INFO "htotal is %d\n", mode->htotal);
		printk(KERN_INFO "VSS is %d\n", mode->vsync_start);
		printk(KERN_INFO "VSE is %d\n", mode->vsync_end);
		printk(KERN_INFO "vtotal is %d\n", mode->vtotal);
		printk(KERN_INFO "clock is %d\n", mode->clock);
#endif
		mode_dev->panel_fixed_mode = mode;
	}


	if (mode_dev->panel_fixed_mode == NULL && mode_dev->vbt_mode)
		mode_dev->panel_fixed_mode = drm_mode_duplicate(dev,
						mode_dev->vbt_mode);


	if (mode_dev->panel_fixed_mode == NULL)
		if (dev_priv->lfp_lvds_vbt_mode)
			mode_dev->panel_fixed_mode =
				drm_mode_duplicate(dev,
					dev_priv->lfp_lvds_vbt_mode);


	if (mode_dev->panel_fixed_mode == NULL)
		return;

	drm_mode_set_name(mode_dev->panel_fixed_mode);
	drm_mode_set_crtcinfo(mode_dev->panel_fixed_mode, 0);
}
