ixgbe_ptp_start_cyclecounter(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct cyclecounter cc;
	unsigned long flags;
	u32 incval = 0;
	u32 tsauxc = 0;
	u32 fuse0 = 0;


	cc.mask = CLOCKSOURCE_MASK(64);
	cc.mult = 1;
	cc.shift = 0;

	switch (hw->mac.type) {
	case ixgbe_mac_X550EM_x:


		fuse0 = IXGBE_READ_REG(hw, IXGBE_FUSES0_GROUP(0));
		if (!(fuse0 & IXGBE_FUSES0_300MHZ)) {
			cc.mult = 3;
			cc.shift = 2;
		}

	case ixgbe_mac_X550:
		cc.read = ixgbe_ptp_read_X550;


		IXGBE_WRITE_REG(hw, IXGBE_SYSTIMR, 0);
		IXGBE_WRITE_REG(hw, IXGBE_SYSTIML, 0);
		IXGBE_WRITE_REG(hw, IXGBE_SYSTIMH, 0);
		tsauxc = IXGBE_READ_REG(hw, IXGBE_TSAUXC);
		IXGBE_WRITE_REG(hw, IXGBE_TSAUXC,
				tsauxc & ~IXGBE_TSAUXC_DISABLE_SYSTIME);
		IXGBE_WRITE_REG(hw, IXGBE_TSIM, IXGBE_TSIM_TXTS);
		IXGBE_WRITE_REG(hw, IXGBE_EIMS, IXGBE_EIMS_TIMESYNC);

		IXGBE_WRITE_FLUSH(hw);
		break;
	case ixgbe_mac_X540:
		cc.read = ixgbe_ptp_read_82599;

		ixgbe_ptp_link_speed_adjust(adapter, &cc.shift, &incval);
		IXGBE_WRITE_REG(hw, IXGBE_TIMINCA, incval);
		break;
	case ixgbe_mac_82599EB:
		cc.read = ixgbe_ptp_read_82599;

		ixgbe_ptp_link_speed_adjust(adapter, &cc.shift, &incval);
		incval >>= IXGBE_INCVAL_SHIFT_82599;
		cc.shift -= IXGBE_INCVAL_SHIFT_82599;
		IXGBE_WRITE_REG(hw, IXGBE_TIMINCA,
				(1 << IXGBE_INCPER_SHIFT_82599) | incval);
		break;
	default:

		return;
	}


	ACCESS_ONCE(adapter->base_incval) = incval;
	smp_mb();


	spin_lock_irqsave(&adapter->tmreg_lock, flags);
	memcpy(&adapter->hw_cc, &cc, sizeof(adapter->hw_cc));
	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);
}
