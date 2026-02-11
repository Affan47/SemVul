bnxt_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_link_info *link_info = &bp->link_info;
	u16 ethtool_speed;

	cmd->supported = bnxt_fw_to_ethtool_support_spds(link_info);

	if (link_info->auto_link_speeds)
		cmd->supported |= SUPPORTED_Autoneg;

	if (BNXT_AUTO_MODE(link_info->auto_mode)) {
		cmd->advertising =
			bnxt_fw_to_ethtool_advertised_spds(link_info);
		cmd->advertising |= ADVERTISED_Autoneg;
		cmd->autoneg = AUTONEG_ENABLE;
	} else {
		cmd->autoneg = AUTONEG_DISABLE;
		cmd->advertising = 0;
	}
	if (link_info->auto_pause_setting & BNXT_LINK_PAUSE_BOTH) {
		if ((link_info->auto_pause_setting & BNXT_LINK_PAUSE_BOTH) ==
		    BNXT_LINK_PAUSE_BOTH) {
			cmd->advertising |= ADVERTISED_Pause;
			cmd->supported |= SUPPORTED_Pause;
		} else {
			cmd->advertising |= ADVERTISED_Asym_Pause;
			cmd->supported |= SUPPORTED_Asym_Pause;
			if (link_info->auto_pause_setting &
			    BNXT_LINK_PAUSE_RX)
				cmd->advertising |= ADVERTISED_Pause;
		}
	} else if (link_info->force_pause_setting & BNXT_LINK_PAUSE_BOTH) {
		if ((link_info->force_pause_setting & BNXT_LINK_PAUSE_BOTH) ==
		    BNXT_LINK_PAUSE_BOTH) {
			cmd->supported |= SUPPORTED_Pause;
		} else {
			cmd->supported |= SUPPORTED_Asym_Pause;
			if (link_info->force_pause_setting &
			    BNXT_LINK_PAUSE_RX)
				cmd->supported |= SUPPORTED_Pause;
		}
	}

	cmd->port = PORT_NONE;
	if (link_info->media_type == PORT_PHY_QCFG_RESP_MEDIA_TYPE_TP) {
		cmd->port = PORT_TP;
		cmd->supported |= SUPPORTED_TP;
		cmd->advertising |= ADVERTISED_TP;
	} else {
		cmd->supported |= SUPPORTED_FIBRE;
		cmd->advertising |= ADVERTISED_FIBRE;

		if (link_info->media_type == PORT_PHY_QCFG_RESP_MEDIA_TYPE_DAC)
			cmd->port = PORT_DA;
		else if (link_info->media_type ==
			 PORT_PHY_QCFG_RESP_MEDIA_TYPE_FIBRE)
			cmd->port = PORT_FIBRE;
	}

	if (link_info->phy_link_status == BNXT_LINK_LINK) {
		if (link_info->duplex & BNXT_LINK_DUPLEX_FULL)
			cmd->duplex = DUPLEX_FULL;
	} else {
		cmd->duplex = DUPLEX_UNKNOWN;
	}
	ethtool_speed = bnxt_fw_to_ethtool_speed(link_info->link_speed);
	ethtool_cmd_speed_set(cmd, ethtool_speed);
	if (link_info->transceiver ==
		PORT_PHY_QCFG_RESP_TRANSCEIVER_TYPE_XCVR_INTERNAL)
		cmd->transceiver = XCVR_INTERNAL;
	else
		cmd->transceiver = XCVR_EXTERNAL;
	cmd->phy_address = link_info->phy_addr;

	return 0;
}
