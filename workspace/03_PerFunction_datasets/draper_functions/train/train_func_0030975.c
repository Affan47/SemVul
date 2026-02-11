amdgpu_atombios_dp_link_train(struct drm_encoder *encoder,
			    struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig;
	struct amdgpu_connector *amdgpu_connector;
	struct amdgpu_connector_atom_dig *dig_connector;
	struct amdgpu_atombios_dp_link_train_info dp_info;
	u8 tmp;

	if (!amdgpu_encoder->enc_priv)
		return;
	dig = amdgpu_encoder->enc_priv;

	amdgpu_connector = to_amdgpu_connector(connector);
	if (!amdgpu_connector->con_priv)
		return;
	dig_connector = amdgpu_connector->con_priv;

	if ((dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_DISPLAYPORT) &&
	    (dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_eDP))
		return;

	if (drm_dp_dpcd_readb(&amdgpu_connector->ddc_bus->aux, DP_MAX_LANE_COUNT, &tmp)
	    == 1) {
		if (tmp & DP_TPS3_SUPPORTED)
			dp_info.tp3_supported = true;
		else
			dp_info.tp3_supported = false;
	} else {
		dp_info.tp3_supported = false;
	}

	memcpy(dp_info.dpcd, dig_connector->dpcd, DP_RECEIVER_CAP_SIZE);
	dp_info.adev = adev;
	dp_info.encoder = encoder;
	dp_info.connector = connector;
	dp_info.dp_lane_count = dig_connector->dp_lane_count;
	dp_info.dp_clock = dig_connector->dp_clock;
	dp_info.aux = &amdgpu_connector->ddc_bus->aux;

	if (amdgpu_atombios_dp_link_train_init(&dp_info))
		goto done;
	if (amdgpu_atombios_dp_link_train_cr(&dp_info))
		goto done;
	if (amdgpu_atombios_dp_link_train_ce(&dp_info))
		goto done;
done:
	if (amdgpu_atombios_dp_link_train_finish(&dp_info))
		return;
}
