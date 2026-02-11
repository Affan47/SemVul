send_data_packet (tap_packet *pkt)
{
  vpndata_packet *p = new vpndata_packet;
  int tos = 0;


  if (conf->inherit_tos && pkt->is_ipv4 ())
    tos = (*pkt)[15] & IPTOS_TOS_MASK;

  p->setup (this, conf->id, &((*pkt)[6 + 6]), pkt->len - 6 - 6, ++oseqno);
  send_vpn_packet (p, si, tos);

  delete p;

  if (oseqno > MAX_SEQNO)
    rekey ();
}
