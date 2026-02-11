ssb_sdio_scan_switch_coreidx(struct ssb_bus *bus, u8 coreidx)
{
	u32 sbaddr;
	int error;

	sbaddr = (coreidx * SSB_CORE_SIZE) + SSB_ENUM_BASE;
	sdio_claim_host(bus->host_sdio);
	error = ssb_sdio_set_sbaddr_window(bus, sbaddr);
	sdio_release_host(bus->host_sdio);
	if (error) {
		dev_err(ssb_sdio_dev(bus), "failed to switch to core %u,"
			" error %d\n", coreidx, error);
		goto out;
	}
out:
	return error;
}
