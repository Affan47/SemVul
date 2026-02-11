nv_alloc_rx ( struct forcedeth_private *priv )
{
	struct ring_desc *rx_curr_desc;
	int i;
	u32 status;

	DBGP ( "nv_alloc_rx\n" );

	for ( i = 0; i < RX_RING_SIZE; i++ ) {
		rx_curr_desc = priv->rx_ring + i;
		status = le32_to_cpu ( rx_curr_desc->flaglen );


		if ( status & NV_RX_AVAIL )
			continue;


		if ( priv->rx_iobuf[i] != NULL )
			continue;


		if ( ! ( priv->rx_iobuf[i] = alloc_iob ( RX_BUF_SZ ) ) ) {
			DBG ( "Refill rx_ring failed, size %d\n", RX_BUF_SZ );
			break;
		}

		rx_curr_desc->buf =
			cpu_to_le32 ( virt_to_bus ( priv->rx_iobuf[i]->data ) );
		wmb();
		rx_curr_desc->flaglen =
			cpu_to_le32 ( RX_BUF_SZ | NV_RX_AVAIL );
	}
}
