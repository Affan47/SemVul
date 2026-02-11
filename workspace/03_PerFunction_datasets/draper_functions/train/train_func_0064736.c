fcoe_interface_cleanup(struct fcoe_interface *fcoe)
{
	struct net_device *netdev = fcoe->netdev;
	struct fcoe_ctlr *fip = fcoe_to_ctlr(fcoe);

	rtnl_lock();
	if (!fcoe->removed)
		fcoe_interface_remove(fcoe);
	rtnl_unlock();


	fcoe_ctlr_destroy(fip);
	scsi_host_put(fip->lp->host);
	dev_put(netdev);
	module_put(THIS_MODULE);
}
