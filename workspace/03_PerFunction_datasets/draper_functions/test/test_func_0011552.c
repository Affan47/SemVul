qlcnic_83xx_clear_lb_mode(struct qlcnic_adapter *adapter, u8 mode)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u32 config = ahw->port_config, max_wait_count;
	struct net_device *netdev = adapter->netdev;
	int status = 0, loop = 0;

	ahw->extend_lb_time = 0;
	max_wait_count = QLC_83XX_LB_WAIT_COUNT;
	set_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
	if (mode == QLCNIC_ILB_MODE)
		ahw->port_config &= ~QLC_83XX_CFG_LOOPBACK_HSS;
	if (mode == QLCNIC_ELB_MODE)
		ahw->port_config &= ~QLC_83XX_CFG_LOOPBACK_EXT;

	status = qlcnic_83xx_set_port_config(adapter);
	if (status) {
		netdev_err(netdev,
			   "Failed to Clear Loopback Mode = 0x%x.\n",
			   ahw->port_config);
		ahw->port_config = config;
		clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
		return status;
	}


	do {
		msleep(QLC_83XX_LB_MSLEEP_COUNT);

		if (test_bit(__QLCNIC_RESETTING, &adapter->state)) {
			netdev_info(netdev,
				    "Device is resetting, free LB test resources\n");
			clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
			return -EBUSY;
		}

		if (ahw->extend_lb_time)
			qlcnic_extend_lb_idc_cmpltn_wait(adapter,
							 &max_wait_count);

		if (loop++ > max_wait_count) {
			netdev_err(netdev, "%s: Did not receive loopback IDC completion AEN\n",
				   __func__);
			clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
			return -ETIMEDOUT;
		}
	} while (test_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status));

	qlcnic_sre_macaddr_change(adapter, adapter->mac_addr, 0,
				  QLCNIC_MAC_DEL);
	return status;
}
