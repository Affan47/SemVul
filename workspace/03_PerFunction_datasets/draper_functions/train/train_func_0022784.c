send_routing_message(unsigned char type, struct routeinfo *node_table, int start, int end,
				struct dn_naddr *exec, int interface)
{
    struct sockaddr_ll sock_info;
    unsigned char packet[1600];
    unsigned short sum;
    int i,j;

    fprintf(stderr,"Sending message type %d. start=%d, end=%d\n", type,start,end);

    i=0;

    packet[i++] = 0x00;
    packet[i++] = 0x00;

    packet[i++] = type;
    packet[i++] = exec->a_addr[0];
    packet[i++] = exec->a_addr[1];
    packet[i++] = 0x00;


    packet[i++] = (end-start) & 0xFF;
    packet[i++] = (end-start) >> 8;
    packet[i++] = start & 0xFF;
    packet[i++] = start >> 8;

    for (j=start; j<end; j++)
    {
	if (node_table[j].valid)
	{
		packet[i++] = node_table[j].cost;
		packet[i++] = (node_table[j].hops << 2) | ((node_table[j].cost>>8) & 3);
	}
	else
	{
	    packet[i++] = 0xff;
	    packet[i++] = 0x7f;
	}
    }


    sum = route_csum(packet, 6, i);
    packet[i++] = sum & 0xFF;
    packet[i++] = sum >> 8;

    packet[0] = (i-2) & 0xFF;
    packet[1] = (i-2) >> 8;


    sock_info.sll_family   = AF_PACKET;
    sock_info.sll_protocol = htons(ETH_P_DNA_RT);
    sock_info.sll_ifindex  = interface;
    sock_info.sll_hatype   = 0;
    sock_info.sll_pkttype  = PACKET_MULTICAST;
    sock_info.sll_halen    = 6;


    sock_info.sll_addr[0]  = 0xab;
    sock_info.sll_addr[1]  = 0x00;
    sock_info.sll_addr[2]  = 0x00;
    sock_info.sll_addr[3]  = 0x03;
    sock_info.sll_addr[4]  = 0x00;
    sock_info.sll_addr[5]  = 0x00;

    if (sendto(dnet_socket, packet, i, 0,
	       (struct sockaddr *)&sock_info, sizeof(sock_info)) < 0)
    {
	    perror("sendto");
	    return -1;
    }
    return 0;
}
