simple_action(Packet *p_in)
{
  WritablePacket *p = p_in->push(sizeof(click_ip));
  if (!p) return 0;

  click_ip *ip = reinterpret_cast<click_ip *>(p->data());
  memcpy(ip, &_iph, sizeof(click_ip));
  if (ip->ip_len) {
      ip->ip_dst = p->dst_ip_anno();
      update_cksum(ip, 16);
      update_cksum(ip, 18);
  } else
      p->set_dst_ip_anno(IPAddress(ip->ip_dst));
  ip->ip_len = htons(p->length());
  ip->ip_id = htons(_id.fetch_and_add(1));
  update_cksum(ip, 2);
  update_cksum(ip, 4);

  p->set_ip_header(ip, sizeof(click_ip));

  return p;
}
