efab_receive ( struct efab_nic *efab, unsigned int id, int len, int drop )
{
	struct efab_rx_queue *rx_queue = &efab->rx_queue;
	struct io_buffer *iob;
	unsigned int read_ptr = rx_queue->read_ptr % EFAB_RXD_SIZE;
	unsigned int buf_ptr = rx_queue->read_ptr % EFAB_NUM_RX_DESC;

	assert ( id == read_ptr );


	iob = rx_queue->buf[buf_ptr];
	rx_queue->buf[buf_ptr] = NULL;

	EFAB_TRACE ( "popping rx_buf[%d] iob %p data %p with %d bytes %s\n",
		     id, iob, iob->data, len, drop ? "bad" : "ok" );


	if ( drop )
		free_iob ( iob );
	else {
		iob_put ( iob, len );
		netdev_rx ( efab->netdev, iob );
	}

	++rx_queue->read_ptr;
}
