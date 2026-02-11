dump_igmp(packet_t *pkt)
{
  igmp_header_t igmp;
  char holder[HOLDER_SIZE];


  set_layer(LAYER_NETWORK);


  stats_update(STATS_IGMP);


  if (get_packet_bytes((u_int8_t *) &igmp, pkt, 8) == 0)
    return;


  igmp.checksum = ntohs(igmp.checksum);


  if (my_args->m)
    {

      display_minimal_string("| IGMP ");
      display_minimal_string(map2str(igmp_type_map, igmp.type));
      display_minimal_string(" ");
    }
  else
    {

      display_header_banner("IGMP Header");


      snprintf(holder, HOLDER_SIZE, "%d (%s)", igmp.type,
	      map2str(igmp_type_map, igmp.type));
      display_string("Type", holder);
      display("Max response time", (u_int8_t *) &igmp.max_resp_time, 1,
	      DISP_DEC);
      display("Checksum", (u_int8_t *) &igmp.checksum, 2, DISP_DEC);


      if (igmp.type != IGMP_TYPE_DVMRP)
	display_ipv4("Group address", (u_int8_t *) &igmp.address);
    }
}
