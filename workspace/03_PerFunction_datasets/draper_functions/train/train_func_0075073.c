bgav_packet_set_text_subtitle(bgav_packet_t * p,
                                   const char * text,
                                   int len,
                                   int64_t start,
                                   int64_t duration)
  {
  if(len < 0)
    len = strlen(text);

  bgav_packet_alloc(p, len+2);
  memcpy(p->data, text, len);
  p->data_size = len;
  PACKET_SET_KEYFRAME(p);
  p->pts = start;
  p->duration = duration;
  p->data_size = len + 1;
  p->data[len]   = '\0';
  p->data[len+1] = '\0';
  }
