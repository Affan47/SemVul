xgbe_dcb_ieee_getpfc(struct net_device *netdev,
				struct ieee_pfc *pfc)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);


	pfc->pfc_cap = pdata->hw_feat.tc_cnt;

	if (pdata->pfc) {
		pfc->pfc_en = pdata->pfc->pfc_en;
		pfc->mbc = pdata->pfc->mbc;
		pfc->delay = pdata->pfc->delay;
	}

	return 0;
}
