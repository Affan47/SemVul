iTCO_wdt_ping(struct watchdog_device *wd_dev)
{
	spin_lock(&iTCO_wdt_private.io_lock);

	iTCO_vendor_pre_keepalive(iTCO_wdt_private.smi_res, wd_dev->timeout);


	if (iTCO_wdt_private.iTCO_version >= 2) {
		outw(0x01, TCO_RLD);
	} else if (iTCO_wdt_private.iTCO_version == 1) {


		outw(0x0008, TCO1_STS);

		outb(0x01, TCO_RLD);
	}

	spin_unlock(&iTCO_wdt_private.io_lock);
	return 0;
}
