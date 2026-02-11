gst_bz2enc_event (GstPad * pad, GstEvent * e)
{
  GstBz2enc *b;
  gboolean ret;

  b = GST_BZ2ENC (gst_pad_get_parent (pad));
  switch (GST_EVENT_TYPE (e)) {
    case GST_EVENT_EOS:{
      GstFlowReturn flow;
      int r = BZ_FINISH_OK;

      do {
        GstBuffer *out;

        flow = gst_pad_alloc_buffer (b->src, b->offset, b->buffer_size,
            GST_PAD_CAPS (b->src), &out);

        if (flow != GST_FLOW_OK) {
          GST_DEBUG_OBJECT (b, "pad alloc on EOS failed: %s",
              gst_flow_get_name (flow));
          break;
        }

        b->stream.next_out = (char *) GST_BUFFER_DATA (out);
        b->stream.avail_out = GST_BUFFER_SIZE (out);
        r = BZ2_bzCompress (&b->stream, BZ_FINISH);
        if ((r != BZ_FINISH_OK) && (r != BZ_STREAM_END)) {
          GST_ELEMENT_ERROR (b, STREAM, ENCODE, (NULL),
              ("Failed to finish to compress (error code %i).", r));
          gst_buffer_unref (out);
          break;
        }

        if (b->stream.avail_out >= GST_BUFFER_SIZE (out)) {
          gst_buffer_unref (out);
          break;
        }

        GST_BUFFER_SIZE (out) -= b->stream.avail_out;
        GST_BUFFER_OFFSET (out) =
            b->stream.total_out_lo32 - GST_BUFFER_SIZE (out);

        flow = gst_pad_push (b->src, out);

        if (flow != GST_FLOW_OK) {
          GST_DEBUG_OBJECT (b, "push on EOS failed: %s",
              gst_flow_get_name (flow));
          break;
        }
      } while (r != BZ_STREAM_END);

      ret = gst_pad_event_default (pad, e);

      if (r != BZ_STREAM_END || flow != GST_FLOW_OK)
        ret = FALSE;

      gst_bz2enc_compress_init (b);
      break;
    }
    default:
      ret = gst_pad_event_default (pad, e);
      break;
  }

  gst_object_unref (b);

  return ret;
}
