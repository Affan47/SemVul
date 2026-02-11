igbvf_free_rx_resources ( struct igbvf_adapter *adapter )
{
	int i;

	DBG ( "igbvf_free_rx_resources\n" );

	free_dma ( adapter->rx_base, adapter->rx_ring_size );

	for ( i = 0; i < NUM_RX_DESC; i++ ) {
		free_iob ( adapter->rx_iobuf[i] );
	}
}
