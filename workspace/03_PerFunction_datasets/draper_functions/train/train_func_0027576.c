fcoe_ddp_done(struct fc_lport *lport, u16 xid)
{
	struct net_device *netdev = fcoe_netdev(lport);

	if (netdev->netdev_ops->ndo_fcoe_ddp_done)
		return netdev->netdev_ops->ndo_fcoe_ddp_done(netdev, xid);
	return 0;
}
