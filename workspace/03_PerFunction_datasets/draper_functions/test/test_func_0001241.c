fcoe_ctlr_enabled(struct fcoe_ctlr_device *cdev)
{
	struct fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(cdev);
	struct fc_lport *lport = ctlr->lp;
	struct net_device *netdev = fcoe_netdev(lport);

	switch (cdev->enabled) {
	case FCOE_CTLR_ENABLED:
		return fcoe_enable(netdev);
	case FCOE_CTLR_DISABLED:
		return fcoe_disable(netdev);
	case FCOE_CTLR_UNUSED:
	default:
		return -ENOTSUPP;
	};
}
