gst_scaletempo_transform (GstBaseTransform * trans,
    GstBuffer * inbuf, GstBuffer * outbuf)
{
  GstScaletempo *scaletempo = GST_SCALETEMPO (trans);
  GstScaletempoPrivate *p = GST_SCALETEMPO_GET_PRIVATE (scaletempo);

  gint8 *pout = (gint8 *) GST_BUFFER_DATA (outbuf);
  guint offset_in = fill_queue (scaletempo, inbuf, 0);
  guint bytes_out = 0;
  while (p->bytes_queued >= p->bytes_queue_max) {
    guint bytes_off = 0;
    gdouble frames_to_slide;
    guint frames_to_stride_whole;


    if (p->output_overlap) {
      if (p->best_overlap_offset) {
        bytes_off = p->best_overlap_offset (scaletempo);
      }
      p->output_overlap (scaletempo, pout, bytes_off);
    }
    memcpy (pout + p->bytes_overlap,
        p->buf_queue + bytes_off + p->bytes_overlap, p->bytes_standing);
    pout += p->bytes_stride;
    bytes_out += p->bytes_stride;


    memcpy (p->buf_overlap,
        p->buf_queue + bytes_off + p->bytes_stride, p->bytes_overlap);
    frames_to_slide = p->frames_stride_scaled + p->frames_stride_error;
    frames_to_stride_whole = (gint) frames_to_slide;
    p->bytes_to_slide = frames_to_stride_whole * p->bytes_per_frame;
    p->frames_stride_error = frames_to_slide - frames_to_stride_whole;

    offset_in += fill_queue (scaletempo, inbuf, offset_in);
  }

  GST_BUFFER_SIZE (outbuf) = bytes_out;
  GST_BUFFER_TIMESTAMP (outbuf) =
      (GST_BUFFER_TIMESTAMP (outbuf) - p->segment_start) / p->scale +
      p->segment_start;

  return GST_FLOW_OK;
}
