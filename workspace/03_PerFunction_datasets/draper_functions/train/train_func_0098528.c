lbs_start_card(struct lbs_private *priv)
{
	struct net_device *dev = priv->dev;
	int ret = -1;

	lbs_deb_enter(LBS_DEB_MAIN);


	ret = lbs_setup_firmware(priv);
	if (ret)
		goto done;

	if (!lbs_disablemesh)
		lbs_init_mesh(priv);
	else
		pr_info("%s: mesh disabled\n", dev->name);

	if (lbs_cfg_register(priv)) {
		pr_err("cannot register device\n");
		goto done;
	}

	if (lbs_mesh_activated(priv))
		lbs_start_mesh(priv);

	lbs_debugfs_init_one(priv, dev);

	netdev_info(dev, "Marvell WLAN 802.11 adapter\n");

	ret = 0;

done:
	lbs_deb_leave_args(LBS_DEB_MAIN, "ret %d", ret);
	return ret;
}
