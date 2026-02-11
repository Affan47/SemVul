ds1wm_up(struct ds1wm_data *ds1wm_data)
{
	int divisor;
	struct device *dev = &ds1wm_data->pdev->dev;
	struct ds1wm_driver_data *plat = dev_get_platdata(dev);

	if (ds1wm_data->cell->enable)
		ds1wm_data->cell->enable(ds1wm_data->pdev);

	divisor = ds1wm_find_divisor(plat->clock_rate);
	dev_dbg(dev, "found divisor 0x%x for clock %d\n",
		divisor, plat->clock_rate);
	if (divisor == 0) {
		dev_err(dev, "no suitable divisor for %dHz clock\n",
			plat->clock_rate);
		return;
	}
	ds1wm_write_register(ds1wm_data, DS1WM_CLKDIV, divisor);


	msleep(1);

	ds1wm_reset(ds1wm_data);
}
