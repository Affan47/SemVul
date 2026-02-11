amdgpu_atombios_encoder_set_backlight_level(struct amdgpu_encoder *amdgpu_encoder,
				     u8 level)
{
	struct drm_encoder *encoder = &amdgpu_encoder->base;
	struct drm_device *dev = amdgpu_encoder->base.dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder_atom_dig *dig;

	if (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		return;

	if ((amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
	    amdgpu_encoder->enc_priv) {
		dig = amdgpu_encoder->enc_priv;
		dig->backlight_level = level;
		amdgpu_atombios_encoder_set_backlight_level_to_reg(adev, dig->backlight_level);

		switch (amdgpu_encoder->encoder_id) {
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			if (dig->backlight_level == 0)
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);
			else {
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL, 0, 0);
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_LCD_BLON, 0, 0);
			}
			break;
		default:
			break;
		}
	}
}
