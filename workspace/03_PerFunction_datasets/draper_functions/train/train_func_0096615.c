xgbe_rx_buf1_len(struct xgbe_ring_data *rdata,
				     struct xgbe_packet_data *packet)
{

	if (!XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES, FIRST))
		return 0;


	if (rdata->rx.hdr_len)
		return rdata->rx.hdr_len;


	if (!XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES, LAST))
		return rdata->rx.hdr.dma_len;


	return min_t(unsigned int, rdata->rx.hdr.dma_len, rdata->rx.len);
}
