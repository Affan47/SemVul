bnad_set_rx_ucast_fltr(struct bnad *bnad)
{
	struct net_device *netdev = bnad->netdev;
	int uc_count = netdev_uc_count(netdev);
	enum bna_cb_status ret;
	u8 *mac_list;
	struct netdev_hw_addr *ha;
	int entry;

	if (netdev_uc_empty(bnad->netdev)) {
		bna_rx_ucast_listset(bnad->rx_info[0].rx, 0, NULL);
		return;
	}

	if (uc_count > bna_attr(&bnad->bna)->num_ucmac)
		goto mode_default;

	mac_list = kzalloc(uc_count * ETH_ALEN, GFP_ATOMIC);
	if (mac_list == NULL)
		goto mode_default;

	entry = 0;
	netdev_for_each_uc_addr(ha, netdev) {
		ether_addr_copy(&mac_list[entry * ETH_ALEN], &ha->addr[0]);
		entry++;
	}

	ret = bna_rx_ucast_listset(bnad->rx_info[0].rx, entry, mac_list);
	kfree(mac_list);

	if (ret != BNA_CB_SUCCESS)
		goto mode_default;

	return;


mode_default:
	bnad->cfg_flags |= BNAD_CF_DEFAULT;
	bna_rx_ucast_listset(bnad->rx_info[0].rx, 0, NULL);
}
