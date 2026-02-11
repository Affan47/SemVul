efab_alloc_resources ( struct efab_nic *efab )
{
	struct efab_ev_queue *ev_queue = &efab->ev_queue;
	struct efab_rx_queue *rx_queue = &efab->rx_queue;
	struct efab_tx_queue *tx_queue = &efab->tx_queue;
	size_t bytes;


	bytes = sizeof ( falcon_event_t ) * EFAB_TXD_SIZE;
	ev_queue->ring = falcon_alloc_special_buffer ( efab, bytes,
						       &ev_queue->entry );
	if ( !ev_queue->ring )
		goto fail1;


	memset ( ev_queue->ring, 0xff, bytes );


	bytes = sizeof ( falcon_tx_desc_t ) * EFAB_TXD_SIZE;
	tx_queue->ring = falcon_alloc_special_buffer ( efab, bytes,
						       &tx_queue->entry );
	if ( ! tx_queue->ring )
		goto fail2;


	bytes = sizeof ( falcon_rx_desc_t ) * EFAB_RXD_SIZE;
	rx_queue->ring = falcon_alloc_special_buffer ( efab, bytes,
						       &rx_queue->entry );
	if ( ! rx_queue->ring )
		goto fail3;

	return 0;

fail3:
	falcon_free_special_buffer ( tx_queue->ring );
	tx_queue->ring = NULL;
fail2:
	falcon_free_special_buffer ( ev_queue->ring );
	ev_queue->ring = NULL;
fail1:
	return -ENOMEM;
}
