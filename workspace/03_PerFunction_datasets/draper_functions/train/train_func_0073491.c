i40e_set_pauseparam(struct net_device *netdev,
			       struct ethtool_pauseparam *pause)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_link_status *hw_link_info = &hw->phy.link_info;
	struct i40e_dcbx_config *dcbx_cfg = &hw->local_dcbx_config;
	bool link_up = hw_link_info->link_info & I40E_AQ_LINK_UP;
	i40e_status status;
	u8 aq_failures;
	int err = 0;


	if (hw->partition_id != 1) {
		i40e_partition_setting_complaint(pf);
		return -EOPNOTSUPP;
	}

	if (vsi != pf->vsi[pf->lan_vsi])
		return -EOPNOTSUPP;

	if (pause->autoneg != ((hw_link_info->an_info & I40E_AQ_AN_COMPLETED) ?
	    AUTONEG_ENABLE : AUTONEG_DISABLE)) {
		netdev_info(netdev, "To change autoneg please use: ethtool -s <dev> autoneg <on|off>\n");
		return -EOPNOTSUPP;
	}


	if (!test_bit(__I40E_DOWN, &pf->state) &&
	    !(hw_link_info->an_info & I40E_AQ_AN_COMPLETED)) {

		netdev_info(netdev, "Autoneg did not complete so changing settings may not result in an actual change.\n");
	}

	if (dcbx_cfg->pfc.pfcenable) {
		netdev_info(netdev,
			    "Priority flow control enabled. Cannot set link flow control.\n");
		return -EOPNOTSUPP;
	}

	if (pause->rx_pause && pause->tx_pause)
		hw->fc.requested_mode = I40E_FC_FULL;
	else if (pause->rx_pause && !pause->tx_pause)
		hw->fc.requested_mode = I40E_FC_RX_PAUSE;
	else if (!pause->rx_pause && pause->tx_pause)
		hw->fc.requested_mode = I40E_FC_TX_PAUSE;
	else if (!pause->rx_pause && !pause->tx_pause)
		hw->fc.requested_mode = I40E_FC_NONE;
	else
		 return -EINVAL;


	i40e_print_link_message(vsi, false);
	netif_carrier_off(netdev);
	netif_tx_stop_all_queues(netdev);


	status = i40e_set_fc(hw, &aq_failures, link_up);

	if (aq_failures & I40E_SET_FC_AQ_FAIL_GET) {
		netdev_info(netdev, "Set fc failed on the get_phy_capabilities call with err %s aq_err %s\n",
			    i40e_stat_str(hw, status),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		err = -EAGAIN;
	}
	if (aq_failures & I40E_SET_FC_AQ_FAIL_SET) {
		netdev_info(netdev, "Set fc failed on the set_phy_config call with err %s aq_err %s\n",
			    i40e_stat_str(hw, status),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		err = -EAGAIN;
	}
	if (aq_failures & I40E_SET_FC_AQ_FAIL_UPDATE) {
		netdev_info(netdev, "Set fc failed on the get_link_info call with err %s aq_err %s\n",
			    i40e_stat_str(hw, status),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		err = -EAGAIN;
	}

	if (!test_bit(__I40E_DOWN, &pf->state)) {

		msleep(75);
		if (!test_bit(__I40E_DOWN, &pf->state))
			return i40e_nway_reset(netdev);
	}

	return err;
}
