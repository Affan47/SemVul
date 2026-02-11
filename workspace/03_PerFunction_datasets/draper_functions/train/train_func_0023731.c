velocity_mii_read(struct mac_regs __iomem *regs, u8 index, u16 *data)
{
	u16 ww;


	safe_disable_mii_autopoll(regs);

	writeb(index, &regs->MIIADR);

	BYTE_REG_BITS_ON(MIICR_RCMD, &regs->MIICR);

	for (ww = 0; ww < W_MAX_TIMEOUT; ww++) {
		if (!(readb(&regs->MIICR) & MIICR_RCMD))
			break;
	}

	*data = readw(&regs->MIIDATA);

	enable_mii_autopoll(regs);
	if (ww == W_MAX_TIMEOUT)
		return -ETIMEDOUT;
	return 0;
}
