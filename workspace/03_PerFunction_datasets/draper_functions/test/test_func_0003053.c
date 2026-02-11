ena_com_get_next_rx_cdesc(
	struct ena_com_io_cq *io_cq)
{
	struct ena_eth_io_rx_cdesc_base *cdesc;
	u16 expected_phase, head_masked;
	u16 desc_phase;

	head_masked = io_cq->head & (io_cq->q_depth - 1);
	expected_phase = io_cq->phase;

	cdesc = (struct ena_eth_io_rx_cdesc_base *)(io_cq->cdesc_addr.virt_addr
			+ (head_masked * io_cq->cdesc_entry_size_in_bytes));

	desc_phase = (READ_ONCE(cdesc->status) & ENA_ETH_IO_RX_CDESC_BASE_PHASE_MASK) >>
			ENA_ETH_IO_RX_CDESC_BASE_PHASE_SHIFT;

	if (desc_phase != expected_phase)
		return NULL;

	return cdesc;
}
