fjes_hw_reset(struct fjes_hw *hw)
{
	union REG_DCTL dctl;
	int timeout;

	dctl.reg = 0;
	dctl.bits.reset = 1;
	wr32(XSCT_DCTL, dctl.reg);

	timeout = FJES_DEVICE_RESET_TIMEOUT * 1000;
	dctl.reg = rd32(XSCT_DCTL);
	while ((dctl.bits.reset == 1) && (timeout > 0)) {
		msleep(1000);
		dctl.reg = rd32(XSCT_DCTL);
		timeout -= 1000;
	}

	return timeout > 0 ? 0 : -EIO;
}
