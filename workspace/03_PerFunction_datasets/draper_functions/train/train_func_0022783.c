at76_get_hw_config(struct at76_priv *priv)
{
	int ret;
	union at76_hwcfg *hwcfg = kmalloc(sizeof(*hwcfg), GFP_KERNEL);

	if (!hwcfg)
		return -ENOMEM;

	if (at76_is_intersil(priv->board_type)) {
		ret = at76_get_hw_cfg_intersil(priv->udev, hwcfg,
					       sizeof(hwcfg->i));
		if (ret < 0)
			goto exit;
		memcpy(priv->mac_addr, hwcfg->i.mac_addr, ETH_ALEN);
		priv->regulatory_domain = hwcfg->i.regulatory_domain;
	} else if (at76_is_503rfmd(priv->board_type)) {
		ret = at76_get_hw_cfg(priv->udev, hwcfg, sizeof(hwcfg->r3));
		if (ret < 0)
			goto exit;
		memcpy(priv->mac_addr, hwcfg->r3.mac_addr, ETH_ALEN);
		priv->regulatory_domain = hwcfg->r3.regulatory_domain;
	} else {
		ret = at76_get_hw_cfg(priv->udev, hwcfg, sizeof(hwcfg->r5));
		if (ret < 0)
			goto exit;
		memcpy(priv->mac_addr, hwcfg->r5.mac_addr, ETH_ALEN);
		priv->regulatory_domain = hwcfg->r5.regulatory_domain;
	}

exit:
	kfree(hwcfg);
	if (ret < 0)
		wiphy_err(priv->hw->wiphy, "cannot get HW Config (error %d)\n",
			  ret);

	return ret;
}
