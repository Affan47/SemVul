wl12xx_get_hw_info(struct wl1271 *wl)
{
	int ret;

	ret = wlcore_read_reg(wl, REG_CHIP_ID_B, &wl->chip.id);
	if (ret < 0)
		goto out;

	wl->fuse_oui_addr = 0;
	wl->fuse_nic_addr = 0;

	ret = wl->ops->get_pg_ver(wl, &wl->hw_pg_ver);
	if (ret < 0)
		goto out;

	if (wl->ops->get_mac)
		ret = wl->ops->get_mac(wl);

out:
	return ret;
}
