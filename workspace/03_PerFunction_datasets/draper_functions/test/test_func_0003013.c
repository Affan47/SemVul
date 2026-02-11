i40e_open(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	int err;


	if (test_bit(__I40E_TESTING, &pf->state) ||
	    test_bit(__I40E_BAD_EEPROM, &pf->state))
		return -EBUSY;

	netif_carrier_off(netdev);

	err = i40e_vsi_open(vsi);
	if (err)
		return err;


	wr32(&pf->hw, I40E_GLLAN_TSOMSK_F, be32_to_cpu(TCP_FLAG_PSH |
						       TCP_FLAG_FIN) >> 16);
	wr32(&pf->hw, I40E_GLLAN_TSOMSK_M, be32_to_cpu(TCP_FLAG_PSH |
						       TCP_FLAG_FIN |
						       TCP_FLAG_CWR) >> 16);
	wr32(&pf->hw, I40E_GLLAN_TSOMSK_L, be32_to_cpu(TCP_FLAG_CWR) >> 16);

#ifdef CONFIG_I40E_VXLAN
	vxlan_get_rx_port(netdev);
#endif
#ifdef CONFIG_I40E_GENEVE
	if (pf->flags & I40E_FLAG_GENEVE_OFFLOAD_CAPABLE)
		geneve_get_rx_port(netdev);
#endif

	return 0;
}
