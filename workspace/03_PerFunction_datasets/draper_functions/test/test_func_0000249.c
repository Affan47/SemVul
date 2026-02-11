ns2501_mode_valid(struct intel_dvo_device *dvo,
					      struct drm_display_mode *mode)
{
	DRM_DEBUG_KMS
	    ("is mode valid (hdisplay=%d,htotal=%d,vdisplay=%d,vtotal=%d)\n",
	     mode->hdisplay, mode->htotal, mode->vdisplay, mode->vtotal);


	if ((mode->hdisplay == 640 && mode->vdisplay == 480 && mode->clock == 25175) ||
	    (mode->hdisplay == 800 && mode->vdisplay == 600 && mode->clock == 40000) ||
	    (mode->hdisplay == 1024 && mode->vdisplay == 768 && mode->clock == 65000)) {
		return MODE_OK;
	} else {
		return MODE_ONE_SIZE;
	}
}
