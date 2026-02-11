regmap_spmi_ext_gather_write(void *context,
					const void *reg, size_t reg_size,
					const void *val, size_t val_size)
{
	int err = 0;
	size_t len;
	u16 addr;

	BUG_ON(reg_size != 2);

	addr = *(u16 *)reg;

	while (addr <= 0xFF && val_size) {
		len = min_t(size_t, val_size, 16);

		err = spmi_ext_register_write(context, addr, val, len);
		if (err)
			goto err_out;

		addr += len;
		val += len;
		val_size -= len;
	}

	while (val_size) {
		len = min_t(size_t, val_size, 8);

		err = spmi_ext_register_writel(context, addr, val, len);
		if (err)
			goto err_out;

		addr += len;
		val += len;
		val_size -= len;
	}

err_out:
	return err;
}
