wl18xx_boot_soft_reset(struct wl1271 *wl)
{
	int ret;


	ret = wlcore_write32(wl, WL18XX_ENABLE, 0x0);
	if (ret < 0)
		goto out;


	ret = wlcore_write32(wl, WL18XX_SPARE_A2, 0xffff);

out:
	return ret;
}
