radeon_combios_get_primary_dac_info(struct
								       radeon_encoder
								       *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	uint16_t dac_info;
	uint8_t rev, bg, dac;
	struct radeon_encoder_primary_dac *p_dac = NULL;
	int found = 0;

	p_dac = kzalloc(sizeof(struct radeon_encoder_primary_dac),
			GFP_KERNEL);

	if (!p_dac)
		return NULL;


	dac_info = combios_get_table_offset(dev, COMBIOS_CRT_INFO_TABLE);
	if (dac_info) {
		rev = RBIOS8(dac_info) & 0x3;
		if (rev < 2) {
			bg = RBIOS8(dac_info + 0x2) & 0xf;
			dac = (RBIOS8(dac_info + 0x2) >> 4) & 0xf;
			p_dac->ps2_pdac_adj = (bg << 8) | (dac);
		} else {
			bg = RBIOS8(dac_info + 0x2) & 0xf;
			dac = RBIOS8(dac_info + 0x3) & 0xf;
			p_dac->ps2_pdac_adj = (bg << 8) | (dac);
		}

		if ((dac == 0) || (bg == 0))
			found = 0;
		else
			found = 1;
	}


	if (((dev->pdev->device == 0x5159) &&
	    (dev->pdev->subsystem_vendor == 0x174B) &&
	    (dev->pdev->subsystem_device == 0x7c28)) ||

	   ((dev->pdev->device == 0x514D) &&
	    (dev->pdev->subsystem_vendor == 0x174B) &&
	    (dev->pdev->subsystem_device == 0x7149))) {

		found = 0;
	}

	if (!found)
		radeon_legacy_get_primary_dac_info_from_table(rdev, p_dac);

	return p_dac;
}
