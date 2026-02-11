sst_byt_dsp_wait_for_ready(struct device *dev, struct sst_pdata *pdata)
{
	struct sst_byt *byt = pdata->dsp;
	int err;

	dev_dbg(byt->dev, "wait for dsp reboot\n");

	err = wait_event_timeout(byt->boot_wait, byt->boot_complete,
				 msecs_to_jiffies(IPC_BOOT_MSECS));
	if (err == 0) {
		dev_err(byt->dev, "ipc: error DSP boot timeout\n");
		return -EIO;
	}

	dev_dbg(byt->dev, "dsp rebooted\n");
	return 0;
}
