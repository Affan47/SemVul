rx_cache_find(const struct rx_header *rxh, const struct ip *ip, int sport,
	      int32_t *opcode)
{
	int i;
	struct rx_cache_entry *rxent;
	u_int32_t clip = ip->ip_dst.s_addr;
	u_int32_t sip = ip->ip_src.s_addr;


	i = rx_cache_hint;
	do {
		rxent = &rx_cache[i];
		if (rxent->callnum == rxh->callNumber &&
		    rxent->client.s_addr == clip &&
		    rxent->server.s_addr == sip &&
		    rxent->serviceId == rxh->serviceId &&
		    rxent->dport == sport) {


			rx_cache_hint = i;
			*opcode = rxent->opcode;
			return(1);
		}
		if (++i > RX_CACHE_SIZE)
			i = 0;
	} while (i != rx_cache_hint);


	return(0);
}
