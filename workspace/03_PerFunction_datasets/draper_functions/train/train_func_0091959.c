igbvf_configure_rx ( struct igbvf_adapter *adapter )
{
        struct e1000_hw *hw = &adapter->hw;
        u32 rxdctl;

	DBG ( "igbvf_configure_rx\n" );


        rxdctl = er32 ( RXDCTL(0) );
        ew32 ( RXDCTL(0), rxdctl & ~E1000_RXDCTL_QUEUE_ENABLE );
        msleep ( 10 );


        ew32 ( RDBAL(0), virt_to_bus (adapter->rx_base) );
        ew32 ( RDBAH(0), 0 );
        ew32 ( RDLEN(0), adapter->rx_ring_size );
	adapter->rx_curr = 0;
        ew32 ( RDH(0), 0 );
        ew32 ( RDT(0), 0 );

        rxdctl |= E1000_RXDCTL_QUEUE_ENABLE;
        rxdctl &= 0xFFF00000;
        rxdctl |= IGBVF_RX_PTHRESH;
        rxdctl |= IGBVF_RX_HTHRESH << 8;
        rxdctl |= IGBVF_RX_WTHRESH << 16;

        igbvf_rlpml_set_vf ( hw, adapter->max_frame_size );


        ew32 ( RXDCTL(0), rxdctl );
        ew32 ( RDT(0), NUM_RX_DESC );
}
