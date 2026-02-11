simple_action(Packet *p)
{
  const click_ip *iph = p->ip_header();
  unsigned csum, icmp_len;
  const click_icmp *icmph = p->icmp_header();

  if (!p->has_network_header() || iph->ip_p != IP_PROTO_ICMP)
    return drop(NOT_ICMP, p);

  icmp_len = p->length() - p->transport_header_offset();
  if (icmp_len < sizeof(click_icmp))
    return drop(BAD_LENGTH, p);

  switch (icmph->icmp_type) {

   case ICMP_UNREACH:
   case ICMP_TIMXCEED:
   case ICMP_PARAMPROB:
   case ICMP_SOURCEQUENCH:
   case ICMP_REDIRECT:

    if (icmp_len < sizeof(click_icmp) + 28)
      return drop(BAD_LENGTH, p);
    break;

   case ICMP_TSTAMP:
   case ICMP_TSTAMPREPLY:

    if (icmp_len != sizeof(click_icmp_tstamp))
      return drop(BAD_LENGTH, p);
    break;

   case ICMP_IREQ:
   case ICMP_IREQREPLY:

    if (icmp_len != sizeof(click_icmp))
      return drop(BAD_LENGTH, p);
    break;

   case ICMP_ROUTERADVERT:

   case ICMP_MASKREQ:
   case ICMP_MASKREQREPLY:


   case ICMP_ECHO:
   case ICMP_ECHOREPLY:
   default:

    break;

  }

  csum = click_in_cksum((unsigned char *)icmph, icmp_len) & 0xFFFF;
  if (csum != 0)
    return drop(BAD_CHECKSUM, p);

  return p;
}
