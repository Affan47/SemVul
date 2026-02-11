bnx2x_period_func(struct link_params *params, struct link_vars *vars)
{
	u16 phy_idx;
	struct bnx2x *bp = params->bp;
	for (phy_idx = INT_PHY; phy_idx < MAX_PHYS; phy_idx++) {
		if (params->phy[phy_idx].flags & FLAGS_TX_ERROR_CHECK) {
			bnx2x_set_aer_mmd(params, &params->phy[phy_idx]);
			if (bnx2x_check_half_open_conn(params, vars, 1) !=
			    0)
				DP(NETIF_MSG_LINK, "Fault detection failed\n");
			break;
		}
	}

	if (CHIP_IS_E3(bp)) {
		struct bnx2x_phy *phy = &params->phy[INT_PHY];
		bnx2x_set_aer_mmd(params, phy);
		if ((phy->supported & SUPPORTED_20000baseKR2_Full) &&
		    (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_20G))
			bnx2x_check_kr2_wa(params, vars, phy);
		bnx2x_check_over_curr(params, vars);
		if (vars->rx_tx_asic_rst)
			bnx2x_warpcore_config_runtime(phy, params, vars);

		if ((REG_RD(bp, params->shmem_base +
			    offsetof(struct shmem_region, dev_info.
				port_hw_config[params->port].default_cfg))
		    & PORT_HW_CFG_NET_SERDES_IF_MASK) ==
		    PORT_HW_CFG_NET_SERDES_IF_SFI) {
			if (bnx2x_is_sfp_module_plugged(phy, params)) {
				bnx2x_sfp_tx_fault_detection(phy, params, vars);
			} else if (vars->link_status &
				LINK_STATUS_SFP_TX_FAULT) {

				vars->link_status &= ~LINK_STATUS_SFP_TX_FAULT;
				vars->phy_flags &= ~PHY_SFP_TX_FAULT_FLAG;

				bnx2x_update_mng(params, vars->link_status);
			}
		}
	}
}
