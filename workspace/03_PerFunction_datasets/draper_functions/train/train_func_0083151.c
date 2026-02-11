i40e_fcoe_config_netdev(struct net_device *netdev, struct i40e_vsi *vsi)
{
	struct i40e_hw *hw = &vsi->back->hw;
	struct i40e_pf *pf = vsi->back;

	if (vsi->type != I40E_VSI_FCOE)
		return;

	netdev->features = (NETIF_F_HW_VLAN_CTAG_TX |
			    NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_FILTER);

	netdev->vlan_features = netdev->features;
	netdev->vlan_features &= ~(NETIF_F_HW_VLAN_CTAG_TX |
				   NETIF_F_HW_VLAN_CTAG_RX |
				   NETIF_F_HW_VLAN_CTAG_FILTER);
	netdev->fcoe_ddp_xid = I40E_FCOE_DDP_MAX - 1;
	netdev->features |= NETIF_F_ALL_FCOE;
	netdev->vlan_features |= NETIF_F_ALL_FCOE;
	netdev->hw_features |= netdev->features;
	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->priv_flags |= IFF_SUPP_NOFCS;

	strlcpy(netdev->name, "fcoe%d", IFNAMSIZ-1);
	netdev->mtu = FCOE_MTU;
	SET_NETDEV_DEV(netdev, &pf->pdev->dev);
	SET_NETDEV_DEVTYPE(netdev, &fcoe_netdev_type);


	netdev->dev_port = 1;
	spin_lock_bh(&vsi->mac_filter_list_lock);
	i40e_add_filter(vsi, hw->mac.san_addr, 0, false, false);
	i40e_add_filter(vsi, (u8[6]) FC_FCOE_FLOGI_MAC, 0, false, false);
	i40e_add_filter(vsi, FIP_ALL_FCOE_MACS, 0, false, false);
	i40e_add_filter(vsi, FIP_ALL_ENODE_MACS, 0, false, false);
	spin_unlock_bh(&vsi->mac_filter_list_lock);


	ether_addr_copy(netdev->dev_addr, hw->mac.san_addr);
	ether_addr_copy(netdev->perm_addr, hw->mac.san_addr);

	netdev->netdev_ops = &i40e_fcoe_netdev_ops;
}
