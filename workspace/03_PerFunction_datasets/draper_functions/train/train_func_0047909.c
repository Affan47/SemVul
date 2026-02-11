hns_nic_update_link_status(struct net_device *netdev)
{
	struct hns_nic_priv *priv = netdev_priv(netdev);

	struct hnae_handle *h = priv->ae_handle;
	int state = 1;

	if (priv->phy) {
		if (!genphy_update_link(priv->phy))
			state = priv->phy->link;
		else
			state = 0;
	}
	state = state && h->dev->ops->get_status(h);

	if (state != priv->link) {
		if (state) {
			netif_carrier_on(netdev);
			netif_tx_wake_all_queues(netdev);
			netdev_info(netdev, "link up\n");
		} else {
			netif_carrier_off(netdev);
			netdev_info(netdev, "link down\n");
		}
		priv->link = state;
	}
}
