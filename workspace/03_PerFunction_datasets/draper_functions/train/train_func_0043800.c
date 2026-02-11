cx231xx_read_modify_write_i2c_dword(struct cx231xx *dev, u8 dev_addr,
					u16 saddr, u32 mask, u32 value)
{
	u32 temp;
	int status = 0;

	status = cx231xx_read_i2c_data(dev, dev_addr, saddr, 2, &temp, 4);

	if (status < 0)
		return status;

	temp &= ~mask;
	temp |= value;

	status = cx231xx_write_i2c_data(dev, dev_addr, saddr, 2, temp, 4);

	return status;
}
