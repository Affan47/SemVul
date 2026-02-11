adt7316_show_DAC(struct adt7316_chip_info *chip,
		int channel, char *buf)
{
	u16 data;
	u8 msb, lsb, offset;
	int ret;

	if (channel >= ADT7316_DA_MSB_DATA_REGS ||
		(channel == 0 &&
		(chip->config3 & ADT7316_EN_IN_TEMP_PROP_DACA)) ||
		(channel == 1 &&
		(chip->config3 & ADT7316_EN_EX_TEMP_PROP_DACB)))
		return -EPERM;

	offset = chip->dac_bits - 8;

	if (chip->dac_bits > 8) {
		ret = chip->bus.read(chip->bus.client,
			ADT7316_DA_DATA_BASE + channel * 2, &lsb);
		if (ret)
			return -EIO;
	}

	ret = chip->bus.read(chip->bus.client,
		ADT7316_DA_DATA_BASE + 1 + channel * 2, &msb);
	if (ret)
		return -EIO;

	data = (msb << offset) + (lsb & ((1 << offset) - 1));

	return sprintf(buf, "%d\n", data);
}
