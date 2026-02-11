igbvf_configure_tx ( struct igbvf_adapter *adapter )
{
	struct e1000_hw *hw = &adapter->hw;
	u32 tctl, txdctl;

	DBG ( "igbvf_configure_tx\n" );


	tctl = er32 ( TCTL );
	ew32 ( TCTL, tctl & ~E1000_TCTL_EN );
	e1e_flush();
	mdelay (10);

	ew32 ( TDBAH(0), 0 );
	ew32 ( TDBAL(0), virt_to_bus ( adapter->tx_base ) );
	ew32 ( TDLEN(0), adapter->tx_ring_size );

	DBG ( "E1000_TDBAL(0): %#08x\n",  er32 ( TDBAL(0) ) );
	DBG ( "E1000_TDLEN(0): %d\n",     er32 ( TDLEN(0) ) );


	ew32 ( TDH(0), 0 );
	ew32 ( TDT(0), 0 );

	adapter->tx_head = 0;
	adapter->tx_tail = 0;
	adapter->tx_fill_ctr = 0;

	txdctl = er32(TXDCTL(0));
	txdctl |= E1000_TXDCTL_QUEUE_ENABLE;
	ew32 ( TXDCTL(0), txdctl );

	txdctl = er32 ( TXDCTL(0) );
	txdctl |= E1000_TXDCTL_QUEUE_ENABLE;
	ew32 ( TXDCTL(0), txdctl );


	adapter->txd_cmd  = E1000_ADVTXD_DCMD_EOP | E1000_ADVTXD_DCMD_IFCS;


	adapter->txd_cmd |= E1000_ADVTXD_DCMD_DEXT;


	adapter->txd_cmd |= E1000_ADVTXD_DTYP_DATA;


	adapter->txd_cmd |= E1000_ADVTXD_DCMD_RS;


	tctl &= ~E1000_TCTL_CT;
	tctl |= E1000_TCTL_PSP | E1000_TCTL_RTLC |
		(E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);

	igbvf_config_collision_dist ( hw );


	tctl |= E1000_TCTL_EN;
	ew32(TCTL, tctl);
	e1e_flush();
}
