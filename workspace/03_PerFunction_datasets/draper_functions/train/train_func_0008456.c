oaktrail_hdmi_save(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	struct psb_state *regs = &dev_priv->regs.psb;
	struct psb_pipe *pipeb = &dev_priv->regs.pipe[1];
	int i;


	hdmi_dev->saveDPLL_CTRL = PSB_RVDC32(DPLL_CTRL);
	hdmi_dev->saveDPLL_DIV_CTRL = PSB_RVDC32(DPLL_DIV_CTRL);
	hdmi_dev->saveDPLL_ADJUST = PSB_RVDC32(DPLL_ADJUST);
	hdmi_dev->saveDPLL_UPDATE = PSB_RVDC32(DPLL_UPDATE);
	hdmi_dev->saveDPLL_CLK_ENABLE = PSB_RVDC32(DPLL_CLK_ENABLE);


	pipeb->conf = PSB_RVDC32(PIPEBCONF);
	pipeb->src = PSB_RVDC32(PIPEBSRC);
	pipeb->htotal = PSB_RVDC32(HTOTAL_B);
	pipeb->hblank = PSB_RVDC32(HBLANK_B);
	pipeb->hsync = PSB_RVDC32(HSYNC_B);
	pipeb->vtotal = PSB_RVDC32(VTOTAL_B);
	pipeb->vblank = PSB_RVDC32(VBLANK_B);
	pipeb->vsync = PSB_RVDC32(VSYNC_B);

	hdmi_dev->savePCH_PIPEBCONF = PSB_RVDC32(PCH_PIPEBCONF);
	hdmi_dev->savePCH_PIPEBSRC = PSB_RVDC32(PCH_PIPEBSRC);
	hdmi_dev->savePCH_HTOTAL_B = PSB_RVDC32(PCH_HTOTAL_B);
	hdmi_dev->savePCH_HBLANK_B = PSB_RVDC32(PCH_HBLANK_B);
	hdmi_dev->savePCH_HSYNC_B  = PSB_RVDC32(PCH_HSYNC_B);
	hdmi_dev->savePCH_VTOTAL_B = PSB_RVDC32(PCH_VTOTAL_B);
	hdmi_dev->savePCH_VBLANK_B = PSB_RVDC32(PCH_VBLANK_B);
	hdmi_dev->savePCH_VSYNC_B  = PSB_RVDC32(PCH_VSYNC_B);


	pipeb->cntr = PSB_RVDC32(DSPBCNTR);
	pipeb->stride = PSB_RVDC32(DSPBSTRIDE);
	pipeb->addr = PSB_RVDC32(DSPBBASE);
	pipeb->surf = PSB_RVDC32(DSPBSURF);
	pipeb->linoff = PSB_RVDC32(DSPBLINOFF);
	pipeb->tileoff = PSB_RVDC32(DSPBTILEOFF);


	regs->saveDSPBCURSOR_CTRL = PSB_RVDC32(CURBCNTR);
	regs->saveDSPBCURSOR_BASE = PSB_RVDC32(CURBBASE);
	regs->saveDSPBCURSOR_POS = PSB_RVDC32(CURBPOS);


	for (i = 0; i < 256; i++)
		pipeb->palette[i] = PSB_RVDC32(PALETTE_B + (i << 2));
}
