igb_reset_q_vector(struct igb_adapter *adapter, int v_idx)
{
	struct igb_q_vector *q_vector = adapter->q_vector[v_idx];


	if (!q_vector)
		return;

	if (q_vector->tx.ring)
		adapter->tx_ring[q_vector->tx.ring->queue_index] = NULL;

	if (q_vector->rx.ring)
		adapter->rx_ring[q_vector->rx.ring->queue_index] = NULL;

	netif_napi_del(&q_vector->napi);

}
