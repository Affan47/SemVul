hns_mac_init_ex(struct hns_mac_cb *mac_cb)
{
	int ret;
	struct mac_params param;
	struct mac_driver *drv;

	hns_dsaf_fix_mac_mode(mac_cb);

	memset(&param, 0, sizeof(struct mac_params));
	hns_mac_param_get(&param, mac_cb);

	if (MAC_SPEED_FROM_MODE(param.mac_mode) < MAC_SPEED_10000)
		drv = (struct mac_driver *)hns_gmac_config(mac_cb, &param);
	else
		drv = (struct mac_driver *)hns_xgmac_config(mac_cb, &param);

	if (!drv)
		return -ENOMEM;

	mac_cb->priv.mac = (void *)drv;
	hns_mac_reset(mac_cb);

	hns_mac_adjust_link(mac_cb, mac_cb->speed, !mac_cb->half_duplex);

	ret = hns_mac_port_config_bc_en(mac_cb, mac_cb->mac_id, 0, ENABLE);
	if (ret)
		goto free_mac_drv;

	return 0;

free_mac_drv:
	drv->mac_free(mac_cb->priv.mac);
	mac_cb->priv.mac = NULL;

	return ret;
}
