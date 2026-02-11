psb_intel_cursor_init(struct drm_device *dev,
				  struct gma_crtc *gma_crtc)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 control[3] = { CURACNTR, CURBCNTR, CURCCNTR };
	u32 base[3] = { CURABASE, CURBBASE, CURCBASE };
	struct gtt_range *cursor_gt;

	if (dev_priv->ops->cursor_needs_phys) {


		cursor_gt = psb_gtt_alloc_range(dev, 4 * PAGE_SIZE, "cursor", 1,
						PAGE_SIZE);
		if (!cursor_gt) {
			gma_crtc->cursor_gt = NULL;
			goto out;
		}
		gma_crtc->cursor_gt = cursor_gt;
		gma_crtc->cursor_addr = dev_priv->stolen_base +
							cursor_gt->offset;
	} else {
		gma_crtc->cursor_gt = NULL;
	}

out:
	REG_WRITE(control[gma_crtc->pipe], 0);
	REG_WRITE(base[gma_crtc->pipe], 0);
}
