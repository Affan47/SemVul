tun_send_ip(struct sa_block *s)
{
	int sent, len;
	uint8_t *start;

	start = s->ipsec.rx.buf;
	len   = s->ipsec.rx.buflen;

	if (opt_if_mode == IF_MODE_TAP) {
#ifndef __sun__


		struct ether_header *eth_hdr = (struct ether_header *) (s->ipsec.rx.buf - ETH_HLEN);

		memcpy(eth_hdr->ether_dhost, s->tun_hwaddr, ETH_ALEN);
		memcpy(eth_hdr->ether_shost, s->tun_hwaddr, ETH_ALEN);


		eth_hdr->ether_shost[0] ^= 0x80;
		eth_hdr->ether_type = htons(ETHERTYPE_IP);

		start = (uint8_t *) eth_hdr;
		len += ETH_HLEN;
#endif
	}

	sent = tun_write(s->tun_fd, start, len);
	if (sent != len)
		logmsg(LOG_ERR, "truncated in: %d -> %d\n", len, sent);
	hex_dump("Tx pkt", start, len, NULL);
	return 1;
}
