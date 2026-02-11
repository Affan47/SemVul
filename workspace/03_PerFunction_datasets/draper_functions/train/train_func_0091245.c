simple_action(Packet *p_in)
{
  WritablePacket *p = p_in->uniqueify();


  click_ip *iph = p->ip_header();
  struct in_addr tmpa = iph->ip_src;
  iph->ip_src = iph->ip_dst;
  iph->ip_dst = tmpa;


  if ((iph->ip_p == IP_PROTO_TCP || iph->ip_p == IP_PROTO_UDP) && IP_FIRSTFRAG(iph) && (int)p->length() >= p->transport_header_offset() + 8) {
    click_udp *udph = p->udp_header();
    uint16_t tmpp = udph->uh_sport;
    udph->uh_sport = udph->uh_dport;
    udph->uh_dport = tmpp;
    if (iph->ip_p == IP_PROTO_TCP) {
      click_tcp *tcph = p->tcp_header();
      uint32_t seqn = tcph->th_seq;
      tcph->th_seq = tcph->th_ack;
      tcph->th_ack = seqn;
    }
  }

  return p;
}
