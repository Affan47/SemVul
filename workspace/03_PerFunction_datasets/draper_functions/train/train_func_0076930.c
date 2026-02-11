send_ping(net_addr *addr)
{
	unsigned char data[8];
	int packet_size;


	BUILD_HEADER( PING );
	psnet_send(addr, &data[0], packet_size);
}
