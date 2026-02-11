rt2x00lib_probe_hw(struct rt2x00_dev *rt2x00dev)
{
	struct hw_mode_spec *spec = &rt2x00dev->spec;
	int status;

	if (test_bit(DEVICE_STATE_REGISTERED_HW, &rt2x00dev->flags))
		return 0;


	status = rt2x00lib_probe_hw_modes(rt2x00dev, spec);
	if (status)
		return status;


	rt2x00dev->hw->queues = rt2x00dev->ops->tx_queues;


	rt2x00dev->hw->extra_tx_headroom =
		max_t(unsigned int, IEEE80211_TX_STATUS_HEADROOM,
		      rt2x00dev->extra_tx_headroom);


	if (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_L2PAD))
		rt2x00dev->hw->extra_tx_headroom += RT2X00_L2PAD_SIZE;
	else if (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DMA))
		rt2x00dev->hw->extra_tx_headroom += RT2X00_ALIGN_SIZE;


	rt2x00dev->hw->sta_data_size = sizeof(struct rt2x00_sta);


	if (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_TXSTATUS_FIFO)) {


		int kfifo_size =
			roundup_pow_of_two(rt2x00dev->ops->tx_queues *
					   rt2x00dev->tx->limit *
					   sizeof(u32));

		status = kfifo_alloc(&rt2x00dev->txstatus_fifo, kfifo_size,
				     GFP_KERNEL);
		if (status)
			return status;
	}


#define RT2X00_TASKLET_INIT(taskletname) \
	if (rt2x00dev->ops->lib->taskletname) { \
		tasklet_init(&rt2x00dev->taskletname, \
			     rt2x00dev->ops->lib->taskletname, \
			     (unsigned long)rt2x00dev); \
	}

	RT2X00_TASKLET_INIT(txstatus_tasklet);
	RT2X00_TASKLET_INIT(pretbtt_tasklet);
	RT2X00_TASKLET_INIT(tbtt_tasklet);
	RT2X00_TASKLET_INIT(rxdone_tasklet);
	RT2X00_TASKLET_INIT(autowake_tasklet);

#undef RT2X00_TASKLET_INIT


	status = ieee80211_register_hw(rt2x00dev->hw);
	if (status)
		return status;

	set_bit(DEVICE_STATE_REGISTERED_HW, &rt2x00dev->flags);

	return 0;
}
