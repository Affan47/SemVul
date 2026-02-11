tps65912_read(struct tps65912 *tps65912, u8 reg)
{
	u8 val;
	int err;

	err = tps65912->read(tps65912, reg, 1, &val);
	if (err < 0)
		return err;

	return val;
}
