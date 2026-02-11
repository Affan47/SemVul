qlcnic_83xx_store_beacon(struct qlcnic_adapter *adapter,
				    const char *buf, size_t len)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	unsigned long h_beacon;
	int err;

	if (test_bit(__QLCNIC_RESETTING, &adapter->state))
		return -EIO;

	if (kstrtoul(buf, 2, &h_beacon))
		return -EINVAL;

	qlcnic_get_beacon_state(adapter);

	if (ahw->beacon_state == h_beacon)
		return len;

	rtnl_lock();
	if (!ahw->beacon_state) {
		if (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state)) {
			rtnl_unlock();
			return -EBUSY;
		}
	}

	if (h_beacon)
		err = qlcnic_83xx_config_led(adapter, 1, h_beacon);
	else
		err = qlcnic_83xx_config_led(adapter, 0, !h_beacon);
	if (!err)
		ahw->beacon_state = h_beacon;

	if (!ahw->beacon_state)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);

	rtnl_unlock();
	return len;
}
