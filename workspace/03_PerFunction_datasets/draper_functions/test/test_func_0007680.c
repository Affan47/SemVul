tcp_rx_fin ( struct tcp_connection *tcp, uint32_t seq ) {


	if ( ( tcp->rcv_ack - seq ) > 0 )
		return 0;


	tcp->tcp_state |= TCP_STATE_RCVD ( TCP_FIN );
	tcp_rx_seq ( tcp, 1 );


	tcp_close ( tcp, 0 );

	return 0;
}
