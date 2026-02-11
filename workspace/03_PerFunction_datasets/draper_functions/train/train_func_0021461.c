misc_linuxipchains(u_char *pkt, int pktlen)
{
  ELEM *new, *list = NULL;

  struct ip *iph = (struct ip *)pkt;
  struct udphdr *udp;
  int ip_hl = iph->ip_hl * 4;
  int ip_len = ntohs(iph->ip_len);
  int hlen = 0;
  u_char *data;

  switch (iph->ip_p) {
  case IPPROTO_UDP:
    hlen = UDP_H;
    break;
  case IPPROTO_TCP:
    hlen = 16;
    break;
  default:
    return NULL;
  }
  if (ip_len - ip_hl < hlen)
    return NULL;


  if (!(data = malloc(ip_hl + hlen))) return NULL;
  memcpy(data, pkt, ip_hl + hlen);

  ((struct ip *)data)->ip_len = htons(ip_hl + hlen);
  ((struct ip *)data)->ip_off = htons(IP_MF);

  udp = (struct udphdr *)(data + ip_hl);
  udp->uh_sport = htons(IPCHAINS_SPORT);
  udp->uh_dport = htons(IPCHAINS_DPORT);


  new = list_elem(data, ip_hl + hlen);
  free(data);
  if (!(list = list_add(list, new)))
    return NULL;

  if (!(data = malloc(ip_hl + 4))) return NULL;
  memcpy(data, pkt, ip_hl + 4);

  ((struct ip *)data)->ip_len = htons(ip_hl + 4);
  ((struct ip *)data)->ip_off = htons(IP_MF);


  new = list_elem(data, ip_hl + 4);
  free(data);
  if (!(list = list_add(list, new)))
    return NULL;

  if (!(data = malloc(ip_len - hlen))) return NULL;
  memcpy(data, pkt, ip_hl);
  memcpy(data + ip_hl, pkt + ip_hl + hlen, ip_len - ip_hl - hlen);

  ((struct ip *)data)->ip_len = htons(ip_len - hlen);
  ((struct ip *)data)->ip_off = htons(hlen >> 3);


  new = list_elem(data, ip_len - hlen);
  free(data);
  if (!(list = list_add(list, new)))
    return NULL;

  return (list->head);
}
