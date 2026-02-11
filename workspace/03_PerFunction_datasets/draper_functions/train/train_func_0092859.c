brcmf_sdio_firmware_callback(struct device *dev,
					 const struct firmware *code,
					 void *nvram, u32 nvram_len)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_sdio_dev *sdiodev = bus_if->bus_priv.sdio;
	struct brcmf_sdio *bus = sdiodev->bus;
	int err = 0;
	u8 saveclk;

	brcmf_dbg(TRACE, "Enter: dev=%s\n", dev_name(dev));

	if (!bus_if->drvr)
		return;


	bus->alp_only = true;
	err = brcmf_sdio_download_firmware(bus, code, nvram, nvram_len);
	if (err)
		goto fail;
	bus->alp_only = false;


	bus->sdcnt.tickcnt = 0;
	brcmf_sdio_wd_timer(bus, BRCMF_WD_POLL_MS);

	sdio_claim_host(sdiodev->func[1]);


	brcmf_sdio_clkctl(bus, CLK_AVAIL, false);
	if (bus->clkstate != CLK_AVAIL)
		goto release;


	saveclk = brcmf_sdiod_regrb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, &err);
	if (!err) {
		brcmf_sdiod_regwb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
				  (saveclk | SBSDIO_FORCE_HT), &err);
	}
	if (err) {
		brcmf_err("Failed to force clock for F2: err %d\n", err);
		goto release;
	}


	w_sdreg32(bus, SDPCM_PROT_VERSION << SMB_DATA_VERSION_SHIFT,
		  offsetof(struct sdpcmd_regs, tosbmailboxdata));
	err = sdio_enable_func(sdiodev->func[SDIO_FUNC_2]);


	brcmf_dbg(INFO, "enable F2: err=%d\n", err);


	if (!err) {

		bus->hostintmask = HOSTINTMASK;
		w_sdreg32(bus, bus->hostintmask,
			  offsetof(struct sdpcmd_regs, hostintmask));

		brcmf_sdiod_regwb(sdiodev, SBSDIO_WATERMARK, 8, &err);
	} else {

		sdio_disable_func(sdiodev->func[SDIO_FUNC_2]);
		goto release;
	}

	if (brcmf_chip_sr_capable(bus->ci)) {
		brcmf_sdio_sr_init(bus);
	} else {

		brcmf_sdiod_regwb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
				  saveclk, &err);
	}

	if (err == 0) {
		err = brcmf_sdiod_intr_register(sdiodev);
		if (err != 0)
			brcmf_err("intr register failed:%d\n", err);
	}


	if (err != 0)
		brcmf_sdio_clkctl(bus, CLK_NONE, false);

	sdio_release_host(sdiodev->func[1]);

	err = brcmf_bus_start(dev);
	if (err != 0) {
		brcmf_err("dongle is not responding\n");
		goto fail;
	}
	return;

release:
	sdio_release_host(sdiodev->func[1]);
fail:
	brcmf_dbg(TRACE, "failed: dev=%s, err=%d\n", dev_name(dev), err);
	device_release_driver(dev);
}
