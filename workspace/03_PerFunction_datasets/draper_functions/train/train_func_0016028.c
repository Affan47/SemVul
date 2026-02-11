bgav_sdp_dump(bgav_sdp_t * s)
  {
  int i;
  bgav_dprintf( "Protocol Version: %d\n", s->protocol_version);

  bgav_dprintf( "Origin:\n");

  print_string("  Useraname", s->origin.username);
  bgav_dprintf( "  Session ID: %" PRId64 "\n", s->origin.session_id);
  bgav_dprintf( "  Session Version: %" PRId64 "\n", s->origin.session_version);
  print_string("  Network Type", s->origin.network_type);
  print_string("  Address Type", s->origin.addr_type);
  print_string("  Address", s->origin.addr);

  print_string("  Session name", s->session_name);
  print_string("  Session description", s->session_description);
  print_string("  URI", s->uri);
  print_string("  email", s->email);
  print_string("  phone", s->phone);


  dump_bandwidth_desc(&s->bandwidth);


  dump_key_desc(&s->key);

  dump_attributes(s->attributes);


  bgav_dprintf( "Num Media: %d\n", s->num_media);

  for(i = 0; i < s->num_media; i++)
    {
    dump_media(&s->media[i]);
    }

  }
