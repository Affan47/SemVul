skge_tx_timeout(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);

	netif_printk(skge, timer, KERN_DEBUG, skge->netdev, "tx timeout\n");

	skge_write8(skge->hw, Q_ADDR(txqaddr[skge->port], Q_CSR), CSR_STOP);
	skge_tx_clean(dev);
	netif_wake_queue(dev);
}
