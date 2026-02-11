fill_queue (GstScaletempo * scaletempo, GstBuffer * buf_in, guint offset)
{
  GstScaletempoPrivate *p = GST_SCALETEMPO_GET_PRIVATE (scaletempo);
  guint bytes_in = GST_BUFFER_SIZE (buf_in) - offset;
  guint offset_unchanged = offset;

  if (p->bytes_to_slide > 0) {
    if (p->bytes_to_slide < p->bytes_queued) {
      guint bytes_in_move = p->bytes_queued - p->bytes_to_slide;
      memmove (p->buf_queue, p->buf_queue + p->bytes_to_slide, bytes_in_move);
      p->bytes_to_slide = 0;
      p->bytes_queued = bytes_in_move;
    } else {
      guint bytes_in_skip;
      p->bytes_to_slide -= p->bytes_queued;
      bytes_in_skip = MIN (p->bytes_to_slide, bytes_in);
      p->bytes_queued = 0;
      p->bytes_to_slide -= bytes_in_skip;
      offset += bytes_in_skip;
      bytes_in -= bytes_in_skip;
    }
  }

  if (bytes_in > 0) {
    guint bytes_in_copy = MIN (p->bytes_queue_max - p->bytes_queued, bytes_in);
    memcpy (p->buf_queue + p->bytes_queued,
        GST_BUFFER_DATA (buf_in) + offset, bytes_in_copy);
    p->bytes_queued += bytes_in_copy;
    offset += bytes_in_copy;
  }

  return offset - offset_unchanged;
}
