sda_in(struct qib_devdata *dd, int wait)
{
	int bnum;
	u32 read_val, mask;

	bnum = dd->gpio_sda_num;
	mask = (1UL << bnum);

	dd->f_gpio_mod(dd, 0, 0, mask);
	read_val = dd->f_gpio_mod(dd, 0, 0, 0);
	if (wait)
		i2c_wait_for_writes(dd);
	return (read_val & mask) >> bnum;
}
