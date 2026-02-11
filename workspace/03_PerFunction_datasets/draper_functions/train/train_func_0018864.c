act_stage2_config (NMDevice *device, NMDeviceStateReason *reason)
{
	NMSettingConnection *s_con;
	const char *connection_type;
	NMActStageReturn ret = NM_ACT_STAGE_RETURN_SUCCESS;

	g_return_val_if_fail (reason != NULL, NM_ACT_STAGE_RETURN_FAILURE);

	s_con = NM_SETTING_CONNECTION (device_get_setting (device, NM_TYPE_SETTING_CONNECTION));
	g_assert (s_con);


	connection_type = nm_setting_connection_get_connection_type (s_con);
	if (!strcmp (connection_type, NM_SETTING_WIRED_SETTING_NAME)) {
		NMSetting8021x *security;

		security = (NMSetting8021x *) device_get_setting (device, NM_TYPE_SETTING_802_1X);
		if (security)
			ret = nm_8021x_stage2_config (NM_DEVICE_ETHERNET (device), reason);
	}

	return ret;
}
