mv_u3d_enable(struct mv_u3d *u3d)
{
	struct mv_usb_platform_data *pdata = dev_get_platdata(u3d->dev);
	int retval;

	if (u3d->active)
		return 0;

	if (!u3d->clock_gating) {
		u3d->active = 1;
		return 0;
	}

	dev_dbg(u3d->dev, "enable u3d\n");
	clk_enable(u3d->clk);
	if (pdata->phy_init) {
		retval = pdata->phy_init(u3d->phy_regs);
		if (retval) {
			dev_err(u3d->dev,
				"init phy error %d\n", retval);
			clk_disable(u3d->clk);
			return retval;
		}
	}
	u3d->active = 1;

	return 0;
}
