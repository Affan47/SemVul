cdv_intel_crt_init(struct drm_device *dev,
			struct psb_intel_mode_device *mode_dev)
{

	struct gma_connector *gma_connector;
	struct gma_encoder *gma_encoder;
	struct drm_connector *connector;
	struct drm_encoder *encoder;

	u32 i2c_reg;

	gma_encoder = kzalloc(sizeof(struct gma_encoder), GFP_KERNEL);
	if (!gma_encoder)
		return;

	gma_connector = kzalloc(sizeof(struct gma_connector), GFP_KERNEL);
	if (!gma_connector)
		goto failed_connector;

	connector = &gma_connector->base;
	connector->polled = DRM_CONNECTOR_POLL_HPD;
	drm_connector_init(dev, connector,
		&cdv_intel_crt_connector_funcs, DRM_MODE_CONNECTOR_VGA);

	encoder = &gma_encoder->base;
	drm_encoder_init(dev, encoder,
		&cdv_intel_crt_enc_funcs, DRM_MODE_ENCODER_DAC);

	gma_connector_attach_encoder(gma_connector, gma_encoder);


	i2c_reg = GPIOA;


	gma_encoder->ddc_bus = psb_intel_i2c_create(dev,
							  i2c_reg, "CRTDDC_A");
	if (!gma_encoder->ddc_bus) {
		dev_printk(KERN_ERR, &dev->pdev->dev, "DDC bus registration "
			   "failed.\n");
		goto failed_ddc;
	}

	gma_encoder->type = INTEL_OUTPUT_ANALOG;


	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	drm_encoder_helper_add(encoder, &cdv_intel_crt_helper_funcs);
	drm_connector_helper_add(connector,
					&cdv_intel_crt_connector_helper_funcs);

	drm_connector_register(connector);

	return;
failed_ddc:
	drm_encoder_cleanup(&gma_encoder->base);
	drm_connector_cleanup(&gma_connector->base);
	kfree(gma_connector);
failed_connector:
	kfree(gma_encoder);
	return;
}
