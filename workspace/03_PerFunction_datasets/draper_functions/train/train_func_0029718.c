auok190x_identify(struct auok190xfb_par *par)
{
	struct device *dev = par->info->device;
	u16 data[4];

	pm_runtime_get_sync(dev);

	mutex_lock(&(par->io_lock));

	auok190x_read_cmdargs(par, AUOK190X_CMD_READ_VERSION, 4, data);

	mutex_unlock(&(par->io_lock));

	par->epd_type = data[1] & AUOK190X_VERSION_TEMP_MASK;

	par->panel_size_int = AUOK190X_VERSION_SIZE_INT(data[2]);
	par->panel_size_float = AUOK190X_VERSION_SIZE_FLOAT(data[2]);
	par->panel_model = AUOK190X_VERSION_MODEL(data[2]);

	par->tcon_version = AUOK190X_VERSION_TCON(data[3]);
	par->lut_version = AUOK190X_VERSION_LUT(data[3]);

	dev_dbg(dev, "panel %d.%din, model 0x%x, EPD 0x%x TCON-rev 0x%x, LUT-rev 0x%x",
		par->panel_size_int, par->panel_size_float, par->panel_model,
		par->epd_type, par->tcon_version, par->lut_version);

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);
}
