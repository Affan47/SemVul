mpeg2ps_stream_read_frame (mpeg2ps_stream_t *sptr,
				       u8 **buffer,
				       u32 *buflen,
				       Bool advance_pointers)
{

  if (sptr->is_video) {
    if (mpeg2ps_stream_find_mpeg_video_frame(sptr)) {
      *buffer = sptr->pes_buffer + sptr->pes_buffer_on;
      *buflen = sptr->frame_len;
      if (advance_pointers) {
	sptr->pes_buffer_on += sptr->frame_len;
      }
      return 1;
    }
    return 0;
  } else if (sptr->m_stream_id == 0xbd) {

    if (mpeg2ps_stream_find_ac3_frame(sptr)) {
      *buffer = sptr->pes_buffer + sptr->pes_buffer_on;
      *buflen = sptr->frame_len;
      if (advance_pointers)
	sptr->pes_buffer_on += sptr->frame_len;
      return 1;
    }
    return 0;
  } else if (mpeg2ps_stream_find_mp3_frame(sptr)) {
    *buffer = sptr->pes_buffer + sptr->pes_buffer_on;
    *buflen = sptr->frame_len;
    if (advance_pointers)
      sptr->pes_buffer_on += sptr->frame_len;
    return 1;
  }
  return 0;
}
