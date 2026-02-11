wl18xx_set_mac_and_phy(struct wl1271 *wl)
{
	struct wl18xx_priv *priv = wl->priv;
	struct wl18xx_mac_and_phy_params *params;
	int ret;

	params = kmemdup(&priv->conf.phy, sizeof(*params), GFP_KERNEL);
	if (!params) {
		ret = -ENOMEM;
		goto out;
	}

	ret = wlcore_set_partition(wl, &wl->ptable[PART_PHY_INIT]);
	if (ret < 0)
		goto out;

	ret = wlcore_write(wl, WL18XX_PHY_INIT_MEM_ADDR, params,
			   sizeof(*params), false);

out:
	kfree(params);
	return ret;
}
