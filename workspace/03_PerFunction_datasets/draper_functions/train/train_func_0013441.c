ethcard_send_packet(ETHCARD *ethcard, BYTE *buf, INT len)
{
  	ETH_FRAME *epkt = (ETH_FRAME *)buf;

	struct sockaddr_ll to;
	to.sll_family = AF_PACKET;
	to.sll_protocol = epkt->type;


	to.sll_ifindex = ethcard->iface;


	to.sll_hatype = 0;


	to.sll_pkttype = 0;


	to.sll_halen = 6;
	memset(to.sll_addr, 0, sizeof(to.sll_addr));
	memcpy(to.sll_addr, epkt->dest, 6);


	if( sendto(ethcard->fd, buf, len, 0, (const struct sockaddr *) &to, sizeof(to)) > 0)
	{
		return OK;
	}
	else
	{
		return ERR;
	}
}
