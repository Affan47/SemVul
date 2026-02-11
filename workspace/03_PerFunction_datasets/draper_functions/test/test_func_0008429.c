reset(struct fbtft_par *par)
{
	if (par->gpio.reset == -1)
		return;

	dev_dbg(par->info->device, "%s()\n", __func__);

	gpio_set_value(par->gpio.reset, 0);
	udelay(20);
	gpio_set_value(par->gpio.reset, 1);
	mdelay(120);
}
