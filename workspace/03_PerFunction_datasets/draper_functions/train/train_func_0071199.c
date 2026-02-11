nm_setting_infiniband_get_mtu (NMSettingInfiniband *setting)
{
	g_return_val_if_fail (NM_IS_SETTING_INFINIBAND (setting), 0);

	return NM_SETTING_INFINIBAND_GET_PRIVATE (setting)->mtu;
}
