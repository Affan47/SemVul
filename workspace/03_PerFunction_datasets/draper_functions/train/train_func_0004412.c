dump_etherarp(packet_t *pkt)
{
  ether_arp_t etharp;


  if (get_packet_bytes((u_int8_t *) &etharp, pkt, 20) == 0)
    return;


  if (my_args->m)
    {
      display_minimal_ipv4((u_int8_t *) &etharp.target_protoaddr);
    }
  else
    {
      display("Sender Ether address", (u_int8_t *) &etharp.sender_hwaddr, 6,
	      DISP_HEXCOLONS);
      display_ipv4("Sender IP address",
		   (u_int8_t *) &etharp.sender_protoaddr);
      display("Target Ether address", (u_int8_t *) &etharp.target_hwaddr, 6,
	      DISP_HEXCOLONS);
      display_ipv4("Target IP address",
		   (u_int8_t *) &etharp.target_protoaddr);
    }


  if (!my_args->m)
    {
      int bytes;

      bytes = get_packet_apparentbytesleft(pkt);
      if (bytes > 0)
	set_packet_apparentend(pkt, 0);
    }

}
