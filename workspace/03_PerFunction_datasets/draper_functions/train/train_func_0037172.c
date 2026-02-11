tps65912_clear_bits(struct tps65912 *tps65912, u8 reg, u8 mask)
{
	u8 data;
	int err;

	mutex_lock(&tps65912->io_mutex);
	err = tps65912->read(tps65912, reg, 1, &data);
	if (err) {
		dev_err(tps65912->dev, "Read from reg 0x%x failed\n", reg);
		goto out;
	}

	data &= ~mask;
	err = tps65912->write(tps65912, reg, 1, &data);
	if (err)
		dev_err(tps65912->dev, "Write to reg 0x%x failed\n", reg);

out:
	mutex_unlock(&tps65912->io_mutex);
	return err;
}
