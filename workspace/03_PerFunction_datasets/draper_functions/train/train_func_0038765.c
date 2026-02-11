igb_ptp_reset(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	unsigned long flags;

	if (!(adapter->flags & IGB_FLAG_PTP))
		return;


	igb_ptp_set_timestamp_mode(adapter, &adapter->tstamp_config);

	spin_lock_irqsave(&adapter->tmreg_lock, flags);

	switch (adapter->hw.mac.type) {
	case e1000_82576:

		wr32(E1000_TIMINCA, INCPERIOD_82576 | INCVALUE_82576);
		break;
	case e1000_82580:
	case e1000_i354:
	case e1000_i350:
	case e1000_i210:
	case e1000_i211:
		wr32(E1000_TSAUXC, 0x0);
		wr32(E1000_TSSDP, 0x0);
		wr32(E1000_TSIM, TSYNC_INTERRUPTS);
		wr32(E1000_IMS, E1000_IMS_TS);
		break;
	default:

		goto out;
	}


	if ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211)) {
		struct timespec64 ts = ktime_to_timespec64(ktime_get_real());

		igb_ptp_write_i210(adapter, &ts);
	} else {
		timecounter_init(&adapter->tc, &adapter->cc,
				 ktime_to_ns(ktime_get_real()));
	}
out:
	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);
}
