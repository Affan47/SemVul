radeon_legacy_get_ext_tmds_info_from_table(struct radeon_encoder *encoder,
						struct radeon_encoder_ext_tmds *tmds)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_i2c_bus_rec i2c_bus;


	i2c_bus = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
	tmds->i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);


	switch (rdev->mode_info.connector_table) {
	case CT_POWERBOOK_EXTERNAL:
	case CT_MINI_EXTERNAL:
	default:
		tmds->dvo_chip = DVO_SIL164;
		tmds->slave_addr = 0x70 >> 1;
		break;
	}

	return true;
}
