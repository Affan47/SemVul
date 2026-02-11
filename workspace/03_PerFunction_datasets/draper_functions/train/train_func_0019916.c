i7300_idle_start(void)
{
	u8 new_ctl;
	u8 limit;

	new_ctl = i7300_idle_thrtctl_saved & ~DIMM_THRTCTL_THRMHUNT;
	pci_write_config_byte(fbd_dev, DIMM_THRTCTL, new_ctl);

	limit = throttle_low_limit;
	if (unlikely(limit > MAX_THROTTLE_LOW_LIMIT))
		limit = MAX_THROTTLE_LOW_LIMIT;

	pci_write_config_byte(fbd_dev, DIMM_THRTLOW, limit);

	new_ctl = i7300_idle_thrtctl_saved | DIMM_THRTCTL_THRMHUNT;
	pci_write_config_byte(fbd_dev, DIMM_THRTCTL, new_ctl);
}
