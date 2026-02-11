mid_get_vbt_data_r10(struct drm_psb_private *dev_priv, u32 addr)
{
	struct vbt_r10 vbt;
	void __iomem *gct_virtual;
	struct gct_r10 *gct;
	struct oaktrail_timing_info *dp_ti = &dev_priv->gct_data.DTD;
	struct gct_r10_timing_info *ti;
	int ret = -1;

	if (read_vbt_r10(addr, &vbt))
		return -1;

	gct = kmalloc(sizeof(*gct) * vbt.panel_count, GFP_KERNEL);
	if (!gct)
		return -1;

	gct_virtual = ioremap(addr + sizeof(vbt),
			sizeof(*gct) * vbt.panel_count);
	if (!gct_virtual)
		goto out;
	memcpy_fromio(gct, gct_virtual, sizeof(*gct));
	iounmap(gct_virtual);

	dev_priv->gct_data.bpi = vbt.primary_panel_idx;
	dev_priv->gct_data.Panel_MIPI_Display_Descriptor =
		gct[vbt.primary_panel_idx].Panel_MIPI_Display_Descriptor;

	ti = &gct[vbt.primary_panel_idx].DTD;
	dp_ti->pixel_clock = ti->pixel_clock;
	dp_ti->hactive_hi = ti->hactive_hi;
	dp_ti->hactive_lo = ti->hactive_lo;
	dp_ti->hblank_hi = ti->hblank_hi;
	dp_ti->hblank_lo = ti->hblank_lo;
	dp_ti->hsync_offset_hi = ti->hsync_offset_hi;
	dp_ti->hsync_offset_lo = ti->hsync_offset_lo;
	dp_ti->hsync_pulse_width_hi = ti->hsync_pulse_width_hi;
	dp_ti->hsync_pulse_width_lo = ti->hsync_pulse_width_lo;
	dp_ti->vactive_hi = ti->vactive_hi;
	dp_ti->vactive_lo = ti->vactive_lo;
	dp_ti->vblank_hi = ti->vblank_hi;
	dp_ti->vblank_lo = ti->vblank_lo;
	dp_ti->vsync_offset_hi = ti->vsync_offset_hi;
	dp_ti->vsync_offset_lo = ti->vsync_offset_lo;
	dp_ti->vsync_pulse_width_hi = ti->vsync_pulse_width_hi;
	dp_ti->vsync_pulse_width_lo = ti->vsync_pulse_width_lo;

	ret = 0;
out:
	kfree(gct);
	return ret;
}
