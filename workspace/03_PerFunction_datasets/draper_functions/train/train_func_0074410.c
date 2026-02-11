hw_reset_dac(struct hw *hw)
{
	u32 i;
	u16 gpioorg;
	unsigned int ret;

	if (i2c_unlock(hw))
		return -1;

	do {
		ret = hw_read_pci(hw, 0xEC);
	} while (!(ret & 0x800000));
	hw_write_pci(hw, 0xEC, 0x05);


	for (i = 0; i < 2;  i++) {

		mdelay(100);
		gpioorg = (u16)hw_read_20kx(hw, GPIO);
		gpioorg &= 0xfffd;
		hw_write_20kx(hw, GPIO, gpioorg);
		mdelay(1);
		hw_write_20kx(hw, GPIO, gpioorg | 0x2);
	}

	i2c_write(hw, 0x00180080, 0x01, 0x80);
	i2c_write(hw, 0x00180080, 0x02, 0x10);

	i2c_lock(hw);

	return 0;
}
