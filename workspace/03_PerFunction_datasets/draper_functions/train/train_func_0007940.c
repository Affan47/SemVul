tcp_rx_enqueue ( struct tcp_connection *tcp, uint32_t seq,
			     uint8_t flags, struct io_buffer *iobuf ) {
	struct tcp_rx_queued_header *tcpqhdr;
	struct io_buffer *queued;
	size_t len;
	uint32_t seq_len;


	flags &= TCP_FIN;
	len = iob_len ( iobuf );
	seq_len = ( len + ( flags ? 1 : 0 ) );


	if ( ( ! ( tcp->tcp_state & TCP_STATE_RCVD ( TCP_SYN ) ) ) ||
	     ( tcp_cmp ( seq, tcp->rcv_ack + tcp->rcv_win ) >= 0 ) ||
	     ( tcp_cmp ( seq + seq_len, tcp->rcv_ack ) < 0 ) ||
	     ( seq_len == 0 ) ) {
		free_iob ( iobuf );
		return;
	}


	tcpqhdr = iob_push ( iobuf, sizeof ( *tcpqhdr ) );
	tcpqhdr->seq = seq;
	tcpqhdr->flags = flags;


	list_for_each_entry ( queued, &tcp->rx_queue, list ) {
		tcpqhdr = queued->data;
		if ( tcp_cmp ( seq, tcpqhdr->seq ) < 0 )
			break;
	}
	list_add_tail ( &iobuf->list, &queued->list );
}
