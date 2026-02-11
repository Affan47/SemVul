init_ogg(bgav_stream_t * s)
  {
  rtp_stream_priv_t * sp;
  char * value;
  int config_len_base64;
  int config_len_raw;
  uint8_t * config_buffer;

  sp = s->priv;

  value = find_fmtp(sp->fmtp, "configuration");
  if(!value)
    return 0;

  config_len_base64 = strlen(value);

  config_buffer = malloc(config_len_base64);
  config_len_raw = bgav_base64decode(value,
                                     config_len_base64,
                                     config_buffer,
                                     config_len_base64);


  if(!extract_extradata_ogg(s, config_buffer, config_len_raw))
    {
    free(config_buffer);
    return 0;
    }
  free(config_buffer);

  if(s->type == BGAV_STREAM_VIDEO)
    {
    s->data.video.format.timescale = s->timescale;
    s->data.video.format.frame_duration = 0;
    s->data.video.format.framerate_mode = GAVL_FRAMERATE_VARIABLE;
    }

  sp->process = process_ogg;
  return 1;
  }
