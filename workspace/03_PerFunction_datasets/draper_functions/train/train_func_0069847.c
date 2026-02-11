dump_arp(packet_t *pkt)
{
  arp_header_t arp;


  set_layer(LAYER_DATALINK);


  stats_update(STATS_ARP);


  if (get_packet_bytes((u_int8_t *) &arp, pkt, 8) == 0)
    return;


  arp.hwaddr_format = ntohs(arp.hwaddr_format);
  arp.protoaddr_format = ntohs(arp.protoaddr_format);
  arp.opcode = ntohs(arp.opcode);


  if (my_args->m)
    {
      display_minimal_string("| ARP ");

      display_minimal_string(map2str(arp_opcode_map, arp.opcode));
      display_minimal_string(" ");
    }
  else
    {


      display_header_banner("ARP Header");


      display_strmap_hex("Hardware type", arp.hwaddr_format,
			 arp_hardware_map);


      display_strmap_hex("Protocol type", arp.protoaddr_format,
			 ethertype_map);


      display("Hardware length", (u_int8_t *) &arp.hwaddr_length, 1,
	      DISP_DEC);
      display("Protocol length", (u_int8_t *) &arp.protoaddr_length, 1,
	      DISP_DEC);


      display_strmap("Opcode", arp.opcode, arp_opcode_map);
    }


  switch(arp.hwaddr_format)
    {
    case ARP_HWTYPE_ETHERNET:
    case ARP_HWTYPE_IEEE802:

      switch(arp.protoaddr_format)
	{
	case ETHERTYPE_IP:
	  dump_etherarp(pkt);
	  break;

	default:
	  break;
	}

    default:
      break;
    }


  hexbuffer_flush();

}
