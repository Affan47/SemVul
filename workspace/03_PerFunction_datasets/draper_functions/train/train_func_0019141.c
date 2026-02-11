e1000e_phc_get_syncdevicetime(ktime_t *device,
					 struct system_counterval_t *system,
					 void *ctx)
{
	struct e1000_adapter *adapter = (struct e1000_adapter *)ctx;
	struct e1000_hw *hw = &adapter->hw;
	unsigned long flags;
	int i;
	u32 tsync_ctrl;
	cycle_t dev_cycles;
	cycle_t sys_cycles;

	tsync_ctrl = er32(TSYNCTXCTL);
	tsync_ctrl |= E1000_TSYNCTXCTL_START_SYNC |
		E1000_TSYNCTXCTL_MAX_ALLOWED_DLY_MASK;
	ew32(TSYNCTXCTL, tsync_ctrl);
	for (i = 0; i < MAX_HW_WAIT_COUNT; ++i) {
		udelay(1);
		tsync_ctrl = er32(TSYNCTXCTL);
		if (tsync_ctrl & E1000_TSYNCTXCTL_SYNC_COMP)
			break;
	}

	if (i == MAX_HW_WAIT_COUNT)
		return -ETIMEDOUT;

	dev_cycles = er32(SYSSTMPH);
	dev_cycles <<= 32;
	dev_cycles |= er32(SYSSTMPL);
	spin_lock_irqsave(&adapter->systim_lock, flags);
	*device = ns_to_ktime(timecounter_cyc2time(&adapter->tc, dev_cycles));
	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	sys_cycles = er32(PLTSTMPH);
	sys_cycles <<= 32;
	sys_cycles |= er32(PLTSTMPL);
	*system = convert_art_to_tsc(sys_cycles);

	return 0;
}
