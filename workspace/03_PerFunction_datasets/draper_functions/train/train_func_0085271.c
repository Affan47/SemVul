bgav_find_video_decoder(bgav_stream_t * s)
  {
  bgav_video_decoder_t * cur;
  int i;
  codecs_lock();


  cur = video_decoders;

  while(cur)
    {
    i = 0;
    while(cur->fourccs[i])
      {
      if(cur->fourccs[i] == s->fourcc)
        {
        codecs_unlock();
        return cur;
        }
      else
        i++;
      }
    cur = cur->next;
    }
  codecs_unlock();
  return NULL;
  }
