bnxt_open(struct net_device *dev)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc = 0;

	rc = bnxt_hwrm_func_reset(bp);
	if (rc) {
		netdev_err(bp->dev, "hwrm chip reset failure rc: %x\n",
			   rc);
		rc = -1;
		return rc;
	}
	return __bnxt_open_nic(bp, true, true);
}
