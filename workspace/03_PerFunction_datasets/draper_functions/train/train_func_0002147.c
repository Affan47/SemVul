rt2x00mac_config(struct ieee80211_hw *hw, u32 changed)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	struct ieee80211_conf *conf = &hw->conf;


	if (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		return 0;


	rt2x00queue_stop_queue(rt2x00dev->rx);


	rt2x00lib_config(rt2x00dev, conf, changed);


	rt2x00lib_config_antenna(rt2x00dev, rt2x00dev->default_ant);


	rt2x00queue_start_queue(rt2x00dev->rx);

	return 0;
}
