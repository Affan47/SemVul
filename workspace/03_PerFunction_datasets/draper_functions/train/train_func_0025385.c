xgbe_rx_buf2_len(struct xgbe_ring_data *rdata,
				     struct xgbe_packet_data *packet,
				     unsigned int len)
{

	if (!XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES, LAST))
		return rdata->rx.buf.dma_len;


	return rdata->rx.len - len;
}
