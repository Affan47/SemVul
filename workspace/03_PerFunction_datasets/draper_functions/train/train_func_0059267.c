cherryview_setup_pctx(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long pctx_paddr, paddr;
	struct i915_gtt *gtt = &dev_priv->gtt;
	u32 pcbr;
	int pctx_size = 32*1024;

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));

	pcbr = I915_READ(VLV_PCBR);
	if ((pcbr >> VLV_PCBR_ADDR_SHIFT) == 0) {
		DRM_DEBUG_DRIVER("BIOS didn't set up PCBR, fixing up\n");
		paddr = (dev_priv->mm.stolen_base +
			 (gtt->stolen_size - pctx_size));

		pctx_paddr = (paddr & (~4095));
		I915_WRITE(VLV_PCBR, pctx_paddr);
	}

	DRM_DEBUG_DRIVER("PCBR: 0x%08x\n", I915_READ(VLV_PCBR));
}
