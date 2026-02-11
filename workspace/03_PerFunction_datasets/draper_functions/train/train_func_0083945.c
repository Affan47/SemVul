qlcnic_wait_rom_done(struct qlcnic_adapter *adapter)
{
	long timeout = 0;
	long done = 0;
	int err = 0;

	cond_resched();
	while (done == 0) {
		done = QLCRD32(adapter, QLCNIC_ROMUSB_GLB_STATUS, &err);
		done &= 2;
		if (++timeout >= QLCNIC_MAX_ROM_WAIT_USEC) {
			dev_err(&adapter->pdev->dev,
				"Timeout reached  waiting for rom done");
			return -EIO;
		}
		udelay(1);
	}
	return 0;
}
