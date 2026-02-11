next_packet_duration_from_dts(bgav_packet_timer_t * pt)
  {
  if(pt->num_packets &&
     ((pt->packets[0]->duration > 0) || PACKET_GET_SKIP(pt->packets[0])))
    return 1;

  while(pt->num_packets < 2)
    {
    if(!insert_packet(pt))
      break;
    }
  if(!pt->num_packets)
    return 0;
  set_duration_from_dts(pt, 0);
  return 1;
  }
