insert_packet_pts_from_dts(bgav_packet_timer_t * pt)
  {
  bgav_packet_t * p;
  p = insert_packet(pt);

  if(!p)
    {
    if(pt->num_packets)
      set_duration_from_dts(pt, pt->num_packets-1);
    return NULL;
    }


  if(p->dts == BGAV_TIMESTAMP_UNDEFINED)
    {
    p->dts = p->pts;
    p->pts = BGAV_TIMESTAMP_UNDEFINED;
    }


  if(pt->num_packets > 1)
    set_duration_from_dts(pt, pt->num_packets-2);
  return p;
  }
