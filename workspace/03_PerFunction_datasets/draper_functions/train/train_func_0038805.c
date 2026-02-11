bnad_vlan_rx_add_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
	struct bnad *bnad = netdev_priv(netdev);
	unsigned long flags;

	if (!bnad->rx_info[0].rx)
		return 0;

	mutex_lock(&bnad->conf_mutex);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_rx_vlan_add(bnad->rx_info[0].rx, vid);
	set_bit(vid, bnad->active_vlans);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	mutex_unlock(&bnad->conf_mutex);

	return 0;
}
