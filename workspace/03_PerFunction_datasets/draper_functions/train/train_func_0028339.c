icmp_tx_echo_reply ( struct io_buffer *iobuf,
				struct sockaddr_tcpip *st_dest,
				struct icmp_echo_protocol *echo_protocol ) {
	struct icmp_echo *echo = iobuf->data;
	int rc;


	echo->icmp.type = echo_protocol->reply;


	DBGC ( icmpcol ( st_dest ), "ICMP TX echo reply id %04x seq %04x\n",
	       ntohs ( echo->ident ), ntohs ( echo->sequence ) );
	if ( ( rc = icmp_tx_echo ( iobuf, st_dest, echo_protocol ) ) != 0 )
		return rc;

	return 0;
}
