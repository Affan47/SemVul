brcmf_sdio_buscore_read32(void *ctx, u32 addr)
{
	struct brcmf_sdio_dev *sdiodev = ctx;
	u32 val, rev;

	val = brcmf_sdiod_regrl(sdiodev, addr, NULL);
	if (sdiodev->func[0]->device == SDIO_DEVICE_ID_BROADCOM_4335_4339 &&
	    addr == CORE_CC_REG(SI_ENUM_BASE, chipid)) {
		rev = (val & CID_REV_MASK) >> CID_REV_SHIFT;
		if (rev >= 2) {
			val &= ~CID_ID_MASK;
			val |= BRCM_CC_4339_CHIP_ID;
		}
	}
	return val;
}
