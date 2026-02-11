efab_poll ( struct net_device *netdev )
{
	struct efab_nic *efab = netdev_priv ( netdev );
	struct efab_ev_queue *ev_queue = &efab->ev_queue;
	struct efab_rx_queue *rx_queue = &efab->rx_queue;
	falcon_event_t *evt;


	evt = ev_queue->ring + ev_queue->read_ptr;
	while ( falcon_event_present ( evt ) ) {

		EFAB_TRACE ( "Event at index 0x%x address %p is "
			     EFAB_QWORD_FMT "\n", ev_queue->read_ptr,
			     evt, EFAB_QWORD_VAL ( *evt ) );

		falcon_handle_event ( efab, evt );


		EFAB_SET_QWORD ( *evt );


		ev_queue->read_ptr = ( ( ev_queue->read_ptr + 1 ) %
				       EFAB_EVQ_SIZE );
		evt = ev_queue->ring + ev_queue->read_ptr;
	}


	(void) efab_fill_rx_queue ( efab, rx_queue );


	falcon_clear_interrupts ( efab );


	falcon_eventq_read_ack ( efab, ev_queue );
}
