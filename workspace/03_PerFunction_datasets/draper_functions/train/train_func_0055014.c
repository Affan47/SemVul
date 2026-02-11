dump_dns_questions(packet_t *pkt, u_int8_t num)
{
  char holder[HOLDER_SIZE];
  u_int16_t query_type, query_class;

  while(num > 0)
    {


      parse_ns_labels(pkt, holder);


      if (get_packet_bytes((u_int8_t *) &query_type, pkt, 2) == 0)
	return;
      if (get_packet_bytes((u_int8_t *) &query_class, pkt, 2) == 0)
	return;


      query_type = ntohs(query_type);
      query_class = ntohs(query_class);


      if (my_args->m)
	{
	  display_minimal_string(holder);
	  display_minimal_string(" ");
	}
      else
	{
	  display_string("Query", holder);
	  snprintf(holder, HOLDER_SIZE, "%d (%s)", query_type,
		  map2str(dns_querytype_map, query_type));
	  display_string("  Query type", holder);
	  snprintf(holder, HOLDER_SIZE, "%d (%s)", query_class,
		  map2str(dns_queryclass_map, query_class));
	  display_string("  Query class", holder);
	}

      num --;
    }
}
