xgbe_dcb_ieee_setpfc(struct net_device *netdev,
				struct ieee_pfc *pfc)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);

	netif_dbg(pdata, drv, netdev,
		  "cap=%hhu, en=%#hhx, mbc=%hhu, delay=%hhu\n",
		  pfc->pfc_cap, pfc->pfc_en, pfc->mbc, pfc->delay);

	if (!pdata->pfc) {
		pdata->pfc = devm_kzalloc(pdata->dev, sizeof(*pdata->pfc),
					  GFP_KERNEL);
		if (!pdata->pfc)
			return -ENOMEM;
	}

	memcpy(pdata->pfc, pfc, sizeof(*pdata->pfc));

	pdata->hw_if.config_dcb_pfc(pdata);

	return 0;
}
