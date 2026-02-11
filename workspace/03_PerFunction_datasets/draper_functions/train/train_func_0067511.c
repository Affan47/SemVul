set_dsi_timings(struct drm_encoder *encoder,
			    const struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->crtc);
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(encoder);
	enum port port;
	unsigned int bpp = intel_crtc->config->pipe_bpp;
	unsigned int lane_count = intel_dsi->lane_count;

	u16 hactive, hfp, hsync, hbp, vfp, vsync, vbp;

	hactive = adjusted_mode->crtc_hdisplay;
	hfp = adjusted_mode->crtc_hsync_start - adjusted_mode->crtc_hdisplay;
	hsync = adjusted_mode->crtc_hsync_end - adjusted_mode->crtc_hsync_start;
	hbp = adjusted_mode->crtc_htotal - adjusted_mode->crtc_hsync_end;

	if (intel_dsi->dual_link) {
		hactive /= 2;
		if (intel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK)
			hactive += intel_dsi->pixel_overlap;
		hfp /= 2;
		hsync /= 2;
		hbp /= 2;
	}

	vfp = adjusted_mode->crtc_vsync_start - adjusted_mode->crtc_vdisplay;
	vsync = adjusted_mode->crtc_vsync_end - adjusted_mode->crtc_vsync_start;
	vbp = adjusted_mode->crtc_vtotal - adjusted_mode->crtc_vsync_end;


	hactive = txbyteclkhs(hactive, bpp, lane_count,
			      intel_dsi->burst_mode_ratio);
	hfp = txbyteclkhs(hfp, bpp, lane_count, intel_dsi->burst_mode_ratio);
	hsync = txbyteclkhs(hsync, bpp, lane_count,
			    intel_dsi->burst_mode_ratio);
	hbp = txbyteclkhs(hbp, bpp, lane_count, intel_dsi->burst_mode_ratio);

	for_each_dsi_port(port, intel_dsi->ports) {
		if (IS_BROXTON(dev)) {


			I915_WRITE(BXT_MIPI_TRANS_HACTIVE(port),
				   adjusted_mode->crtc_hdisplay);
			I915_WRITE(BXT_MIPI_TRANS_VACTIVE(port),
				   adjusted_mode->crtc_vdisplay);
			I915_WRITE(BXT_MIPI_TRANS_VTOTAL(port),
				   adjusted_mode->crtc_vtotal);
		}

		I915_WRITE(MIPI_HACTIVE_AREA_COUNT(port), hactive);
		I915_WRITE(MIPI_HFP_COUNT(port), hfp);


		I915_WRITE(MIPI_HSYNC_PADDING_COUNT(port), hsync);
		I915_WRITE(MIPI_HBP_COUNT(port), hbp);


		I915_WRITE(MIPI_VFP_COUNT(port), vfp);
		I915_WRITE(MIPI_VSYNC_PADDING_COUNT(port), vsync);
		I915_WRITE(MIPI_VBP_COUNT(port), vbp);
	}
}
