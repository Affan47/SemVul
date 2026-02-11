intel_opregion_get_panel_type(struct drm_device *dev)
{
	u32 panel_details;
	int ret;

	ret = swsci(dev, SWSCI_GBDA_PANEL_DETAILS, 0x0, &panel_details);
	if (ret) {
		DRM_DEBUG_KMS("Failed to get panel details from OpRegion (%d)\n",
			      ret);
		return ret;
	}

	ret = (panel_details >> 8) & 0xff;
	if (ret > 0x10) {
		DRM_DEBUG_KMS("Invalid OpRegion panel type 0x%x\n", ret);
		return -EINVAL;
	}


	if (ret == 0x0) {
		DRM_DEBUG_KMS("No panel type in OpRegion\n");
		return -ENODEV;
	}


	if (IS_SKYLAKE(dev)) {
		DRM_DEBUG_KMS("Ignoring OpRegion panel type (%d)\n", ret - 1);
		return -ENODEV;
	}

	return ret - 1;
}
