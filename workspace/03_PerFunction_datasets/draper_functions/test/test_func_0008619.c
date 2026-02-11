ipw_prom_hard_start_xmit(struct sk_buff *skb,
					    struct net_device *dev)
{
	IPW_DEBUG_INFO("prom dev->xmit\n");
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}
