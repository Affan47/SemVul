send_packet(u_char *pkt,
	    int pktlen)
{
  static u_char opkt[IP_MAXPACKET];
  struct ip *iph = (struct ip *)pkt;


  if (pktlen < ntohs(iph->ip_len)) return 0;


  if (sropt) {

    memcpy(opkt, pkt, pktlen);

    if (libnet_insert_ipo(sropt, sroptlen, opkt) == -1) {
      perror("send_packet: libnet_insert_ipo");
      return 0;
    }
    iph = (struct ip *)opkt;
    pkt = opkt;
  }
  pktlen = ntohs(iph->ip_len);


  switch( mode ) {
  case MODE_RTEORIG:

    while (libnet_write_ip(raw_socket, pkt, pktlen) != pktlen) {
      perror("libnet_write_ip");
      printf("send_packet failed: ");
      print_ip(pkt, pktlen);
      printf("\n");
      return 0;
    }
    break;

  case MODE_RTESAME:
    if (!send_raw_packet(pkt, pktlen, snd_llmac, rtr_llmac))
      return 0;
      break;

  case MODE_TAKEOVER:
    if (!send_raw_packet(pkt, pktlen, snd_llmac, rtr_llmac))
      return 0;
    break;

  default:
    fprintf(stderr, "Internal error 40 in send.c\n");
    return(0);
  }


  if (verbose >= VERYVERBOSE) {
    print_ip(pkt, pktlen);
    printf("\n");
  }

  return 1;
}
