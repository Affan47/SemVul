set_packet_type(bgav_frametype_detector_t * fd,
                           bgav_packet_t * p)
  {
  int coding_type;

  if(PACKET_GET_KEYFRAME(p))
    {
    coding_type = BGAV_CODING_TYPE_I;
    fd->max_pts = p->pts;
    }
  else if(p->pts < fd->max_pts)
    {
    coding_type = BGAV_CODING_TYPE_B;
    }
  else
    {
    coding_type = BGAV_CODING_TYPE_P;
    fd->max_pts = p->pts;
    }
  PACKET_SET_CODING_TYPE(p, coding_type);
  return coding_type;
  }
