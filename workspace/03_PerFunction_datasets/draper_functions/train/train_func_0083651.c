ican3_open(struct net_device *ndev)
{
	struct ican3_dev *mod = netdev_priv(ndev);
	int ret;


	ret = open_candev(ndev);
	if (ret) {
		netdev_err(mod->ndev, "unable to start CAN layer\n");
		return ret;
	}


	ret = ican3_set_bus_state(mod, true);
	if (ret) {
		netdev_err(mod->ndev, "unable to set bus-on\n");
		close_candev(ndev);
		return ret;
	}


	mod->can.state = CAN_STATE_ERROR_ACTIVE;
	netif_start_queue(ndev);

	return 0;
}
