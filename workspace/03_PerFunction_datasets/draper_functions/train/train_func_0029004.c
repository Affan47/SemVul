bnxt_dcbnl_ieee_delapp(struct net_device *dev, struct dcb_app *app)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc;

	if (!(bp->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST))
		return -EINVAL;

	rc = dcb_ieee_delapp(dev, app);
	if (rc)
		return rc;
	if ((app->selector == IEEE_8021QAZ_APP_SEL_ETHERTYPE &&
	     app->protocol == ETH_P_ROCE) ||
	    (app->selector == IEEE_8021QAZ_APP_SEL_DGRAM &&
	     app->protocol == ROCE_V2_UDP_DPORT))
		rc = bnxt_hwrm_set_dcbx_app(bp, app, false);

	return rc;
}
