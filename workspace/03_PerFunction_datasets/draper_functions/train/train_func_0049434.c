dce_v8_0_afmt_audio_select_pin(struct drm_encoder *encoder)
{
	struct amdgpu_device *adev = encoder->dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	u32 offset;

	if (!dig || !dig->afmt || !dig->afmt->pin)
		return;

	offset = dig->afmt->offset;

	WREG32(mmAFMT_AUDIO_SRC_CONTROL + offset,
	       (dig->afmt->pin->id << AFMT_AUDIO_SRC_CONTROL__AFMT_AUDIO_SRC_SELECT__SHIFT));
}
