send_icmp_echo(void)
{
	char *packet, *data;
	struct myicmphdr *icmp;

	packet = malloc(ICMPHDR_SIZE + data_size);
	if (packet == NULL) {
		perror("[send_icmp] malloc");
		return;
	}

	memset(packet, 0, ICMPHDR_SIZE + data_size);

	icmp = (struct myicmphdr*) packet;
	data = packet + ICMPHDR_SIZE;


	icmp->type = opt_icmptype;
	icmp->code = opt_icmpcode;
	icmp->checksum = 0;
	icmp->un.echo.id = icmp_ip_id == DEFAULT_ICMP_IP_ID ? getpid() & 0xffff : icmp_ip_id;
	icmp->un.echo.sequence = _icmp_seq;


	data_handler(data, data_size);


	if (icmp_cksum == -1)
		icmp->checksum = cksum((u_short*)packet, ICMPHDR_SIZE + data_size);
	else
		icmp->checksum = icmp_cksum;


	if (opt_icmptype == ICMP_ECHO)
		delaytable_add(_icmp_seq, 0, time(NULL), get_usec(), S_SENT);


	send_ip_handler(packet, ICMPHDR_SIZE + data_size);
	free (packet);

	_icmp_seq++;
}
