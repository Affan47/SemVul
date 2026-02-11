brcmf_pcie_buscore_reset(void *ctx, struct brcmf_chip *chip)
{
	struct brcmf_pciedev_info *devinfo = (struct brcmf_pciedev_info *)ctx;
	u32 val;

	devinfo->ci = chip;
	brcmf_pcie_reset_device(devinfo);

	val = brcmf_pcie_read_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT);
	if (val != 0xffffffff)
		brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT,
				       val);

	return 0;
}
