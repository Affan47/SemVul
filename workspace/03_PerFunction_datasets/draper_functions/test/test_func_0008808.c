simple_action(Packet *p_in)
{
    if (WritablePacket *p = p_in->uniqueify()) {
	click_ip *ip;
	unsigned plen, hlen;

	if (!p->has_network_header())
	    goto bad;
	plen = p->network_length();
	if (plen < sizeof(click_ip))
	    goto bad;
	ip = p->ip_header();
	hlen = ip->ip_hl << 2;
	if (hlen < sizeof(click_ip) || hlen > plen)
	    goto bad;

	ip->ip_sum = 0;
	ip->ip_sum = click_in_cksum((unsigned char *)ip, hlen);
	return p;

      bad:
	click_chatter("SetIPChecksum: bad lengths");
	p->kill();
    }
    return 0;
}
