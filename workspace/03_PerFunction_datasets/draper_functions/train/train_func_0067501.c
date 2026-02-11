nes_netdev_set_pauseparam(struct net_device *netdev,
		struct ethtool_pauseparam *et_pauseparam)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;
	u32 u32temp;

	if (et_pauseparam->autoneg) {

		return 0;
	}
	if ((et_pauseparam->tx_pause == 1) && (nesdev->disable_tx_flow_control == 1)) {
		u32temp = nes_read_indexed(nesdev,
				NES_IDX_MAC_TX_CONFIG + (nesdev->mac_index*0x200));
		u32temp |= NES_IDX_MAC_TX_CONFIG_ENABLE_PAUSE;
		nes_write_indexed(nesdev,
				NES_IDX_MAC_TX_CONFIG + (nesdev->mac_index*0x200), u32temp);
		nesdev->disable_tx_flow_control = 0;
	} else if ((et_pauseparam->tx_pause == 0) && (nesdev->disable_tx_flow_control == 0)) {
		u32temp = nes_read_indexed(nesdev,
				NES_IDX_MAC_TX_CONFIG + (nesdev->mac_index*0x200));
		u32temp &= ~NES_IDX_MAC_TX_CONFIG_ENABLE_PAUSE;
		nes_write_indexed(nesdev,
				NES_IDX_MAC_TX_CONFIG + (nesdev->mac_index*0x200), u32temp);
		nesdev->disable_tx_flow_control = 1;
	}
	if ((et_pauseparam->rx_pause == 1) && (nesdev->disable_rx_flow_control == 1)) {
		u32temp = nes_read_indexed(nesdev,
				NES_IDX_MPP_DEBUG + (nesdev->mac_index*0x40));
		u32temp &= ~NES_IDX_MPP_DEBUG_PORT_DISABLE_PAUSE;
		nes_write_indexed(nesdev,
				NES_IDX_MPP_DEBUG + (nesdev->mac_index*0x40), u32temp);
		nesdev->disable_rx_flow_control = 0;
	} else if ((et_pauseparam->rx_pause == 0) && (nesdev->disable_rx_flow_control == 0)) {
		u32temp = nes_read_indexed(nesdev,
				NES_IDX_MPP_DEBUG + (nesdev->mac_index*0x40));
		u32temp |= NES_IDX_MPP_DEBUG_PORT_DISABLE_PAUSE;
		nes_write_indexed(nesdev,
				NES_IDX_MPP_DEBUG + (nesdev->mac_index*0x40), u32temp);
		nesdev->disable_rx_flow_control = 1;
	}

	return 0;
}
