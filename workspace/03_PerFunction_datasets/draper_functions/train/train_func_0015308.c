zd_ioread32v_locked(struct zd_chip *chip, u32 *values, const zd_addr_t *addr,
		 unsigned int count)
{
	int r;
	int i;
	zd_addr_t a16[USB_MAX_IOREAD32_COUNT * 2];
	u16 v16[USB_MAX_IOREAD32_COUNT * 2];
	unsigned int count16;

	if (count > USB_MAX_IOREAD32_COUNT)
		return -EINVAL;


	count16 = 2 * count;
	BUG_ON(count16 * sizeof(zd_addr_t) > sizeof(a16));
	BUG_ON(count16 * sizeof(u16) > sizeof(v16));

	for (i = 0; i < count; i++) {
		int j = 2*i;

		a16[j] = inc_addr(addr[i]);
		a16[j+1] = addr[i];
	}

	r = zd_ioread16v_locked(chip, v16, a16, count16);
	if (r) {
		dev_dbg_f(zd_chip_dev(chip),
			  "error: %s. Error number %d\n", __func__, r);
		return r;
	}

	for (i = 0; i < count; i++) {
		int j = 2*i;
		values[i] = (v16[j] << 16) | v16[j+1];
	}

	return 0;
}
