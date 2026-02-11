tcp_rx_ack ( struct tcp_connection *tcp, uint32_t ack,
			uint32_t win ) {
	uint32_t ack_len = ( ack - tcp->snd_seq );
	size_t len;
	unsigned int acked_flags;


	if ( ack_len > tcp->snd_sent ) {
		DBGC ( tcp, "TCP %p received ACK for %08x..%08x, "
		       "sent only %08x..%08x\n", tcp, tcp->snd_seq,
		       ( tcp->snd_seq + ack_len ), tcp->snd_seq,
		       ( tcp->snd_seq + tcp->snd_sent ) );

		if ( TCP_HAS_BEEN_ESTABLISHED ( tcp->tcp_state ) ) {

			return 0;
		} else {


			return -EINVAL;
		}
	}


	if ( ack_len == 0 )
		return 0;


	stop_timer ( &tcp->timer );


	len = ack_len;
	acked_flags = ( TCP_FLAGS_SENDING ( tcp->tcp_state ) &
			( TCP_SYN | TCP_FIN ) );
	if ( acked_flags ) {
		len--;
		pending_put ( &tcp->pending_flags );
	}


	tcp->snd_seq = ack;
	tcp->snd_sent = 0;
	tcp->snd_win = win;


	tcp_process_tx_queue ( tcp, len, NULL, 1 );


	if ( acked_flags )
		tcp->tcp_state |= TCP_STATE_ACKED ( acked_flags );


	if ( list_empty ( &tcp->tx_queue ) &&
	     ( tcp->flags & TCP_XFER_CLOSED ) &&
	     ! ( tcp->tcp_state & TCP_STATE_SENT ( TCP_FIN ) ) ) {
		tcp->tcp_state |= TCP_STATE_SENT ( TCP_FIN );
		pending_get ( &tcp->pending_flags );
	}

	return 0;
}
