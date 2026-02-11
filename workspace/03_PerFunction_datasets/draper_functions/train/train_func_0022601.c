bgav_pts_cache_get_first(bgav_pts_cache_t * c, int * duration,
                                 gavl_timecode_t * tc)
  {
  int i = get_min_index(c);

  if(i < 0)
    return BGAV_TIMESTAMP_UNDEFINED;
  else
    {
    c->entries[i].used = 0;
    *duration = c->entries[i].duration;
    if(tc)
      *tc = c->entries[i].tc;
    return c->entries[i].pts;
    }
  }
