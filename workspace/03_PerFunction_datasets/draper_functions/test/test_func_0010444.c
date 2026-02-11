init_aac(bgav_stream_t * s)
  {
  bgav_mkv_track_t * p = s->priv;
  if(p->CodecPrivate)
    {
    bgav_stream_set_extradata(s, p->CodecPrivate, p->CodecPrivateLen);
    }
  else
    {
    int profile, sri;
    s->ext_data = malloc(5);
    profile = aac_profile(p->CodecID);
    sri = aac_sri(p->audio.SamplingFrequency);
    s->ext_data[0] = (profile << 3) | ((sri&0x0E) >> 1);
    s->ext_data[1] = ((sri&0x01) << 7) | (p->audio.Channels<<3);
    if(strstr(p->CodecID, "SBR"))
      {
      sri = aac_sri(p->audio.OutputSamplingFrequency);
      s->ext_data[2] = 0x56;
      s->ext_data[3] = 0xE5;
      s->ext_data[4] = 0x80 | (sri<<3);
      s->ext_size = 5;
      p->frame_samples = 2048;
      }
    else
      {
      p->frame_samples = 1024;
      s->ext_size = 2;
      }
    }
  s->fourcc = BGAV_MK_FOURCC('m','p','4','a');
  }
