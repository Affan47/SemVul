wl1271_suspend(struct device *dev)
{


	struct sdio_func *func = dev_to_sdio_func(dev);
	struct wl12xx_sdio_glue *glue = sdio_get_drvdata(func);
	struct wl1271 *wl = platform_get_drvdata(glue->core);
	mmc_pm_flag_t sdio_flags;
	int ret = 0;

	dev_dbg(dev, "wl1271 suspend. wow_enabled: %d\n",
		wl->wow_enabled);


	if (wl->wow_enabled) {
		sdio_flags = sdio_get_host_pm_caps(func);

		if (!(sdio_flags & MMC_PM_KEEP_POWER)) {
			dev_err(dev, "can't keep power while host "
				     "is suspended\n");
			ret = -EINVAL;
			goto out;
		}


		ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
		if (ret) {
			dev_err(dev, "error while trying to keep power\n");
			goto out;
		}
	}
out:
	return ret;
}
