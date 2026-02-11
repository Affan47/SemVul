qlcnic_dev_statistics_len(struct qlcnic_adapter *adapter)
{
	int len = -1;

	if (qlcnic_82xx_check(adapter)) {
		len = qlcnic_82xx_statistics(adapter);
		if (adapter->flags & QLCNIC_ESWITCH_ENABLED)
			len += ARRAY_SIZE(qlcnic_device_gstrings_stats);
	} else if (qlcnic_83xx_check(adapter)) {
		len = qlcnic_83xx_statistics(adapter);
	}

	return len;
}
