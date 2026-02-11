ars_open_rawsocket(struct ars_packet *pkt)
{
	int s;
	const int one = 1;

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1) {
		ars_set_error(pkt, "Can't open the raw socket");
		return -ARS_ERROR;
	}
	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&one,
		sizeof(one)) == -1 ||
	    setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char*)&one,
		sizeof(one)) == -1)
	{
		close(s);
		ars_set_error(pkt, "Can't set socket options");
		return -ARS_ERROR;
	}
	return s;
}
