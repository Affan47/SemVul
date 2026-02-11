prism54_set_txpower(struct net_device *ndev, struct iw_request_info *info,
		    struct iw_param *vwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	s32 u = vwrq->value;


	u *= 4;
	if (vwrq->disabled) {

		printk(KERN_DEBUG
		       "%s: %s() disabling radio is not yet supported.\n",
		       priv->ndev->name, __func__);
		return -ENOTSUPP;
	} else if (vwrq->fixed)

		return mgt_set_request(priv, OID_INL_OUTPUTPOWER, 0, &u);
	else {
		printk(KERN_DEBUG
		       "%s: %s() auto power will be implemented later.\n",
		       priv->ndev->name, __func__);
		return -ENOTSUPP;
	}
}
