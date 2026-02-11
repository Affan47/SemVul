dce6_audio_get_pin(struct radeon_device *rdev)
{
	struct drm_encoder *encoder;
	struct radeon_encoder *radeon_encoder;
	struct radeon_encoder_atom_dig *dig;
	struct r600_audio_pin *pin = NULL;
	int i, pin_count;

	dce6_afmt_get_connected_pins(rdev);

	for (i = 0; i < rdev->audio.num_pins; i++) {
		if (rdev->audio.pin[i].connected) {
			pin = &rdev->audio.pin[i];
			pin_count = 0;

			list_for_each_entry(encoder, &rdev->ddev->mode_config.encoder_list, head) {
				if (radeon_encoder_is_digital(encoder)) {
					radeon_encoder = to_radeon_encoder(encoder);
					dig = radeon_encoder->enc_priv;
					if (dig->pin == pin)
						pin_count++;
				}
			}

			if (pin_count == 0)
				return pin;
		}
	}
	if (!pin)
		DRM_ERROR("No connected audio pins found!\n");
	return pin;
}
