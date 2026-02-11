next_packet_psxstr(bgav_demuxer_context_t * ctx)
  {
  int channel;
  uint8_t sector[RAW_CD_SECTOR_SIZE];
  bgav_stream_t * s;
  bgav_packet_t * p;
  int current_sector;
  int sector_count;
  int frame_size;
  int bytes_to_copy;


  if(bgav_input_read_data(ctx->input, sector, RAW_CD_SECTOR_SIZE) < RAW_CD_SECTOR_SIZE)
    return 0;

  channel = sector[0x11];

  switch (sector[0x12] & CDXA_TYPE_MASK)
    {
    case CDXA_TYPE_DATA:
    case CDXA_TYPE_VIDEO:

      s = bgav_track_find_stream(ctx, channel + VIDEO_OFFSET);
      if(!s)
        break;

      current_sector = BGAV_PTR_2_16LE(&sector[0x1C]);
      sector_count   = BGAV_PTR_2_16LE(&sector[0x1E]);
      frame_size     = BGAV_PTR_2_32LE(&sector[0x24]);
      if(!s->packet)
        {
        s->packet = bgav_stream_get_packet_write(s);
        bgav_packet_alloc(s->packet, frame_size);
        s->packet->data_size = 0;
        }
      bytes_to_copy = frame_size - current_sector*VIDEO_DATA_CHUNK_SIZE;

      if(bytes_to_copy > 0)
        {
        if(bytes_to_copy > VIDEO_DATA_CHUNK_SIZE)
          bytes_to_copy=VIDEO_DATA_CHUNK_SIZE;
        memcpy(s->packet->data + current_sector*VIDEO_DATA_CHUNK_SIZE,
               sector + VIDEO_DATA_HEADER_SIZE, bytes_to_copy);
        s->packet->data_size += bytes_to_copy;
        }

      if(current_sector == sector_count-1)
        {
        s->packet->pts = s->in_position;
        bgav_stream_done_packet_write(s, s->packet);
        s->packet = NULL;
        }
      break;
    case CDXA_TYPE_AUDIO:

      s = bgav_track_find_stream(ctx, channel + AUDIO_OFFSET);
      if(!s)
        break;

      p = bgav_stream_get_packet_write(s);
      bgav_packet_alloc(p, RAW_CD_SECTOR_DATA_SIZE);

      memcpy(p->data, sector + 24, RAW_CD_SECTOR_DATA_SIZE);
      p->data_size = RAW_CD_SECTOR_DATA_SIZE;
      bgav_stream_done_packet_write(s, p);

      break;

    }
  return 1;
  }
