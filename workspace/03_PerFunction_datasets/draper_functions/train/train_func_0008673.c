iwl_set_temperature_offset_calib_v2(struct iwl_priv *priv)
{
	struct iwl_calib_temperature_offset_v2_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	iwl_set_calib_hdr(&cmd.hdr, IWL_PHY_CALIBRATE_TEMP_OFFSET_CMD);
	cmd.radio_sensor_offset_high = priv->nvm_data->kelvin_temperature;
	cmd.radio_sensor_offset_low = priv->nvm_data->raw_temperature;
	if (!cmd.radio_sensor_offset_low) {
		IWL_DEBUG_CALIB(priv, "no info in EEPROM, use default\n");
		cmd.radio_sensor_offset_low = DEFAULT_RADIO_SENSOR_OFFSET;
		cmd.radio_sensor_offset_high = DEFAULT_RADIO_SENSOR_OFFSET;
	}
	cmd.burntVoltageRef = priv->nvm_data->calib_voltage;

	IWL_DEBUG_CALIB(priv, "Radio sensor offset high: %d\n",
			le16_to_cpu(cmd.radio_sensor_offset_high));
	IWL_DEBUG_CALIB(priv, "Radio sensor offset low: %d\n",
			le16_to_cpu(cmd.radio_sensor_offset_low));
	IWL_DEBUG_CALIB(priv, "Voltage Ref: %d\n",
			le16_to_cpu(cmd.burntVoltageRef));

	return iwl_calib_set(priv, (void *)&cmd, sizeof(cmd));
}
