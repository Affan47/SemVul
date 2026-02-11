falcon_reconfigure_xmac ( struct efab_nic *efab )
{
	efab_dword_t reg;
	int max_frame_len;


	EFAB_POPULATE_DWORD_3 ( reg,
				FCN_XM_RX_JUMBO_MODE, 1,
				FCN_XM_TX_STAT_EN, 1,
				FCN_XM_RX_STAT_EN, 1);
	falcon_xmac_writel ( efab, &reg, FCN_XM_GLB_CFG_REG_MAC );


	EFAB_POPULATE_DWORD_6 ( reg,
				FCN_XM_TXEN, 1,
				FCN_XM_TX_PRMBL, 1,
				FCN_XM_AUTO_PAD, 1,
				FCN_XM_TXCRC, 1,
				FCN_XM_FCNTL, 1,
				FCN_XM_IPG, 0x3 );
	falcon_xmac_writel ( efab, &reg, FCN_XM_TX_CFG_REG_MAC );


	EFAB_POPULATE_DWORD_4 ( reg,
				FCN_XM_RXEN, 1,
				FCN_XM_AUTO_DEPAD, 0,
				FCN_XM_ACPT_ALL_MCAST, 1,
				FCN_XM_PASS_CRC_ERR, 1 );
	falcon_xmac_writel ( efab, &reg, FCN_XM_RX_CFG_REG_MAC );


	max_frame_len = EFAB_MAX_FRAME_LEN ( ETH_FRAME_LEN );
	EFAB_POPULATE_DWORD_1 ( reg,
				FCN_XM_MAX_RX_FRM_SIZE, max_frame_len );
	falcon_xmac_writel ( efab, &reg, FCN_XM_RX_PARAM_REG_MAC );
	EFAB_POPULATE_DWORD_2 ( reg,
				FCN_XM_MAX_TX_FRM_SIZE, max_frame_len,
				FCN_XM_TX_JUMBO_MODE, 1 );
	falcon_xmac_writel ( efab, &reg, FCN_XM_TX_PARAM_REG_MAC );


	EFAB_POPULATE_DWORD_2 ( reg,
				FCN_XM_PAUSE_TIME, 0xfffe,
				FCN_XM_DIS_FCNTL, 0 );
	falcon_xmac_writel ( efab, &reg, FCN_XM_FC_REG_MAC );


	EFAB_POPULATE_DWORD_4 ( reg,
				FCN_XM_ADR_0, efab->mac_addr[0],
				FCN_XM_ADR_1, efab->mac_addr[1],
				FCN_XM_ADR_2, efab->mac_addr[2],
				FCN_XM_ADR_3, efab->mac_addr[3] );
	falcon_xmac_writel ( efab, &reg, FCN_XM_ADR_LO_REG_MAC );
	EFAB_POPULATE_DWORD_2 ( reg,
				FCN_XM_ADR_4, efab->mac_addr[4],
				FCN_XM_ADR_5, efab->mac_addr[5] );
	falcon_xmac_writel ( efab, &reg, FCN_XM_ADR_HI_REG_MAC );
}
