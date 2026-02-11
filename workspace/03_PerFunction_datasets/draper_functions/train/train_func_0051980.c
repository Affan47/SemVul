init_speex(bgav_stream_t * s)
  {
  SpeexCallback callback;
  speex_priv_t * priv;

  priv = calloc(1, sizeof(*priv));
  s->data.audio.decoder->priv = priv;

  speex_bits_init(&priv->bits);

  if(!s->ext_data)
    {
    bgav_log(s->opt, BGAV_LOG_ERROR, LOG_DOMAIN, "Speex needs extradata");
    return 0;
    }

  priv->header = speex_packet_to_header((char*)s->ext_data, s->ext_size);

  if(!priv->header)
    return 0;

  priv->dec_state = speex_decoder_init(speex_mode_list[priv->header->mode]);


  s->data.audio.format.sample_format = GAVL_SAMPLE_FLOAT;
  s->data.audio.format.num_channels = priv->header->nb_channels;
  s->data.audio.format.samplerate = priv->header->rate;
  s->data.audio.format.interleave_mode = GAVL_INTERLEAVE_ALL;
  gavl_set_channel_setup(&s->data.audio.format);

  speex_decoder_ctl(priv->dec_state, SPEEX_GET_FRAME_SIZE, &priv->frame_size);
  s->data.audio.format.samples_per_frame = priv->frame_size * priv->header->frames_per_packet;

  priv->frame = gavl_audio_frame_create(&s->data.audio.format);


  if(priv->header->nb_channels > 1)
    {
    memcpy(&priv->stereo, &__stereo, sizeof(__stereo));

    callback.callback_id = SPEEX_INBAND_STEREO;
    callback.func = speex_std_stereo_request_handler;
    callback.data = &priv->stereo;
    speex_decoder_ctl(priv->dec_state, SPEEX_SET_HANDLER, &callback);
    }

  gavl_metadata_set(&s->m, GAVL_META_FORMAT,
                    "Speex");
  return 1;
  }
