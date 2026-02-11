skl_get_buf_trans_hdmi(struct drm_device *dev,
		       int *n_entries)
{
	const struct ddi_buf_trans *ddi_translations;

	if (IS_SKL_ULX(dev)) {
		ddi_translations = skl_y_ddi_translations_hdmi;
		*n_entries = ARRAY_SIZE(skl_y_ddi_translations_hdmi);
	} else {
		ddi_translations = skl_ddi_translations_hdmi;
		*n_entries = ARRAY_SIZE(skl_ddi_translations_hdmi);
	}

	return ddi_translations;
}
