r8153_first_init(struct r8152 *tp)
{
	u32 ocp_data;
	int i;

	rxdy_gated_en(tp, true);
	r8153_teredo_off(tp);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	r8153_hw_phy_cfg(tp);

	rtl8152_nic_reset(tp);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8153_RMS);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_MTPS, MTPS_JUMBO);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR0);
	ocp_data |= TCR0_AUTO_FIFO;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TCR0, ocp_data);

	rtl8152_nic_reset(tp);


	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_NORMAL);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_NORMAL);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_NORMAL);

	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, TXFIFO_THR_NORMAL2);


	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	if (test_bit(DELL_TB_RX_AGG_BUG, &tp->flags))
		ocp_data |= RX_AGG_DISABLE;

	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);
}
