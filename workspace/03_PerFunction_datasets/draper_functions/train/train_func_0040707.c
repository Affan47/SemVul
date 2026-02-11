peek_func(void * pt1, int force)
  {
  bgav_packet_t * p;
  bgav_frametype_detector_t * fd = pt1;

  if(!fd->initialized)
    {
    if(!force)
      return NULL;

    if(!initialize(fd))
      return NULL;
    }

  if(fd->num_packets)
    return fd->packets[0];

  if(!force)
    return NULL;

  p = fd->src.get_func(fd->src.data);
  if(!p)
    return NULL;
  set_packet_type(fd, p);
  put_packet(fd, p);
  return fd->packets[0];
  }
