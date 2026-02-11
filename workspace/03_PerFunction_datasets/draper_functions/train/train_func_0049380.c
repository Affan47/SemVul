validate_rx_req_id(struct ena_ring *rx_ring, u16 req_id)
{
	if (likely(req_id < rx_ring->ring_size))
		return 0;

	netif_err(rx_ring->adapter, rx_err, rx_ring->netdev,
		  "Invalid rx req_id: %hu\n", req_id);

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->rx_stats.bad_req_id++;
	u64_stats_update_end(&rx_ring->syncp);


	rx_ring->adapter->reset_reason = ENA_REGS_RESET_INV_RX_REQ_ID;
	set_bit(ENA_FLAG_TRIGGER_RESET, &rx_ring->adapter->flags);
	return -EFAULT;
}
