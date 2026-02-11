get_next_pts(bgav_packet_timer_t * pt,
                        int start, int end, int current)
  {
  int i;
  int ret = -1;
  int64_t next_pts = 0;

  for(i = start; i < end; i++)
    {
    if(pt->packets[i]->pts <= pt->packets[current]->pts)
      continue;
    if((ret < 0) || (pt->packets[i]->pts < next_pts))
      {
      ret = i;
      next_pts = pt->packets[i]->pts;
      }
    }
  return ret;
  }
