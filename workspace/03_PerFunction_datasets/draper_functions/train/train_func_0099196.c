rt2x00link_start_vcocal(struct rt2x00_dev *rt2x00dev)
{
	struct link *link = &rt2x00dev->link;

	if (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) &&
	    rt2x00dev->ops->lib->vco_calibration)
		ieee80211_queue_delayed_work(rt2x00dev->hw,
					     &link->vco_work,
					     VCO_INTERVAL);
}
