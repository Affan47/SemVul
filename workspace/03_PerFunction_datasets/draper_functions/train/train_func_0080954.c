tcp_rx_seq ( struct tcp_connection *tcp, uint32_t seq_len ) {
	tcp->rcv_ack += seq_len;
	if ( tcp->rcv_win > seq_len ) {
		tcp->rcv_win -= seq_len;
	} else {
		tcp->rcv_win = 0;
	}
}
