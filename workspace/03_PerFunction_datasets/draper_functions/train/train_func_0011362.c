receivePacket(int sock, PPPoEPacket *pkt, int *size)
{
    if ((*size = recv(sock, pkt, sizeof(PPPoEPacket), 0)) < 0) {
	error("error receiving pppoe packet: %m");
	return -1;
    }
    if (debug)
	pppoe_log_packet("Recv ", pkt);
    return 0;
}
