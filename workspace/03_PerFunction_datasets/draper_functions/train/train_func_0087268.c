i40e_config_netdev(struct i40e_vsi *vsi)
{
	u8 brdcast[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_netdev_priv *np;
	struct net_device *netdev;
	u8 mac_addr[ETH_ALEN];
	int etherdev_size;

	etherdev_size = sizeof(struct i40e_netdev_priv);
	netdev = alloc_etherdev_mq(etherdev_size, vsi->alloc_queue_pairs);
	if (!netdev)
		return -ENOMEM;

	vsi->netdev = netdev;
	np = netdev_priv(netdev);
	np->vsi = vsi;

	netdev->hw_enc_features |= NETIF_F_IP_CSUM	       |
				   NETIF_F_IPV6_CSUM	       |
				   NETIF_F_TSO		       |
				   NETIF_F_TSO6		       |
				   NETIF_F_TSO_ECN	       |
				   NETIF_F_GSO_GRE	       |
				   NETIF_F_GSO_UDP_TUNNEL      |
				   NETIF_F_GSO_UDP_TUNNEL_CSUM |
				   0;

	netdev->features = NETIF_F_SG		       |
			   NETIF_F_IP_CSUM	       |
			   NETIF_F_SCTP_CRC	       |
			   NETIF_F_HIGHDMA	       |
			   NETIF_F_GSO_UDP_TUNNEL      |
			   NETIF_F_GSO_GRE	       |
			   NETIF_F_HW_VLAN_CTAG_TX     |
			   NETIF_F_HW_VLAN_CTAG_RX     |
			   NETIF_F_HW_VLAN_CTAG_FILTER |
			   NETIF_F_IPV6_CSUM	       |
			   NETIF_F_TSO		       |
			   NETIF_F_TSO_ECN	       |
			   NETIF_F_TSO6		       |
			   NETIF_F_RXCSUM	       |
			   NETIF_F_RXHASH	       |
			   0;

	if (!(pf->flags & I40E_FLAG_MFP_ENABLED))
		netdev->features |= NETIF_F_NTUPLE;
	if (pf->flags & I40E_FLAG_OUTER_UDP_CSUM_CAPABLE)
		netdev->features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;


	netdev->hw_features |= netdev->features;

	if (vsi->type == I40E_VSI_MAIN) {
		SET_NETDEV_DEV(netdev, &pf->pdev->dev);
		ether_addr_copy(mac_addr, hw->mac.perm_addr);


		if (!i40e_rm_default_mac_filter(vsi, mac_addr)) {
			spin_lock_bh(&vsi->mac_filter_list_lock);
			i40e_add_filter(vsi, mac_addr,
					I40E_VLAN_ANY, false, true);
			spin_unlock_bh(&vsi->mac_filter_list_lock);
		}
	} else {

		snprintf(netdev->name, IFNAMSIZ, "%sv%%d",
			 pf->vsi[pf->lan_vsi]->netdev->name);
		random_ether_addr(mac_addr);

		spin_lock_bh(&vsi->mac_filter_list_lock);
		i40e_add_filter(vsi, mac_addr, I40E_VLAN_ANY, false, false);
		spin_unlock_bh(&vsi->mac_filter_list_lock);
	}

	spin_lock_bh(&vsi->mac_filter_list_lock);
	i40e_add_filter(vsi, brdcast, I40E_VLAN_ANY, false, false);
	spin_unlock_bh(&vsi->mac_filter_list_lock);

	ether_addr_copy(netdev->dev_addr, mac_addr);
	ether_addr_copy(netdev->perm_addr, mac_addr);


	netdev->vlan_features = netdev->features & ~(NETIF_F_HW_VLAN_CTAG_TX |
						     NETIF_F_HW_VLAN_CTAG_RX |
						   NETIF_F_HW_VLAN_CTAG_FILTER);
	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->priv_flags |= IFF_SUPP_NOFCS;

	i40e_vsi_config_netdev_tc(vsi, vsi->tc_config.enabled_tc);

	netdev->netdev_ops = &i40e_netdev_ops;
	netdev->watchdog_timeo = 5 * HZ;
	i40e_set_ethtool_ops(netdev);
#ifdef I40E_FCOE
	i40e_fcoe_config_netdev(netdev, vsi);
#endif

	return 0;
}
