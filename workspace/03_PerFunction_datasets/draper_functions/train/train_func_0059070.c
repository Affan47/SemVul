init_compressed_theora(void * data,
                                  gavl_video_format_t * format,
                                  const gavl_compression_info_t * ci,
                                  gavl_metadata_t * metadata)
  {
  ogg_packet packet;

  theora_t * theora = data;
  uint8_t * ptr;
  uint32_t len;
  uint8_t * comment_packet;
  int comment_len;
  int vendor_len;

  theora->format = format;
  theora->compressed = 1;
  ogg_stream_init(&theora->os, theora->serialno);

  memset(&packet, 0, sizeof(packet));


  ptr = ci->global_header;

  len = PTR_2_32BE(ptr); ptr += 4;

  packet.packet = ptr;
  packet.bytes  = len;
  packet.b_o_s = 1;

  theora->ti.keyframe_granule_shift =
    (char) ((ptr[40] & 0x03) << 3);

  theora->ti.keyframe_granule_shift |=
    (ptr[41] & 0xe0) >> 5;

  ogg_stream_packetin(&theora->os,&packet);
  if(!bg_ogg_flush_page(&theora->os, theora->output, 1))
    bg_log(BG_LOG_ERROR, LOG_DOMAIN,  "Got no theora ID page");
  ptr += len;


  len = PTR_2_32BE(ptr); ptr += 4;

  build_comment(&theora->tc, metadata);


  vendor_len = PTR_2_32LE(ptr + 7);
  theora->tc.vendor = calloc(1, vendor_len + 1);
  memcpy(theora->tc.vendor, ptr + 11, vendor_len);
  fprintf(stderr, "Got vendor %s\n", theora->tc.vendor);

  comment_packet = create_comment_packet(&theora->tc, &comment_len);
  packet.packet = comment_packet;
  packet.bytes  = comment_len;
  packet.b_o_s = 0;

  ogg_stream_packetin(&theora->os,&packet);

  free(comment_packet);

  free(theora->tc.vendor);
  theora->tc.vendor = NULL;

  ptr += len;


  len = PTR_2_32BE(ptr); ptr += 4;

  packet.packet = ptr;
  packet.bytes  = len;

  ogg_stream_packetin(&theora->os,&packet);

  theora->frames_since_keyframe = -1;

  return 1;

  }
