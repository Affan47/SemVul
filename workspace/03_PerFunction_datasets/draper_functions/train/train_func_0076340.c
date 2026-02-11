simple_action(Packet *p)
{
  const click_ip *iph = p->ip_header();
  const click_udp *udph = p->udp_header();
  unsigned len, iph_len;

  if (!iph || iph->ip_p != IP_PROTO_UDP)
    return drop(NOT_UDP, p);

  iph_len = iph->ip_hl << 2;
  len = ntohs(udph->uh_ulen);
  if (len < sizeof(click_udp)
      || p->length() < len + iph_len + p->network_header_offset())
    return drop(BAD_LENGTH, p);

  if (udph->uh_sum != 0) {
    unsigned csum = click_in_cksum((unsigned char *)udph, len);
    if (click_in_cksum_pseudohdr(csum, iph, len) != 0)
      return drop(BAD_CHECKSUM, p);
  }

  return p;
}
