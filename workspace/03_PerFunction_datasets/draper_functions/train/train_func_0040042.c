gst_rnd_buffer_size_loop (GstRndBufferSize * self)
{
  GstBuffer *buf = NULL;
  GstFlowReturn ret;
  guint num_bytes, size;

  if (G_UNLIKELY (self->min > self->max))
    goto bogus_minmax;

  if (G_UNLIKELY (self->min != self->max)) {
    num_bytes = g_rand_int_range (self->rand, self->min, self->max);
  } else {
    num_bytes = self->min;
  }

  GST_LOG_OBJECT (self, "pulling %u bytes at offset %" G_GUINT64_FORMAT,
      num_bytes, self->offset);

  ret = gst_pad_pull_range (self->sinkpad, self->offset, num_bytes, &buf);

  if (ret != GST_FLOW_OK)
    goto pull_failed;

  size = gst_buffer_get_size (buf);

  if (size < num_bytes) {
    GST_WARNING_OBJECT (self, "short buffer: %u bytes", size);
  }

  if (self->need_newsegment) {
    GstSegment segment;

    gst_segment_init (&segment, GST_FORMAT_BYTES);
    segment.start = self->offset;
    gst_pad_push_event (self->srcpad, gst_event_new_segment (&segment));
    self->need_newsegment = FALSE;
  }

  self->offset += size;

  ret = gst_pad_push (self->srcpad, buf);

  if (ret != GST_FLOW_OK)
    goto push_failed;

  return;

pause_task:
  {
    GST_DEBUG_OBJECT (self, "pausing task");
    gst_pad_pause_task (self->sinkpad);
    return;
  }

pull_failed:
  {
    if (ret == GST_FLOW_EOS) {
      GST_DEBUG_OBJECT (self, "eos");
      gst_pad_push_event (self->srcpad, gst_event_new_eos ());
    } else {
      GST_WARNING_OBJECT (self, "pull_range flow: %s", gst_flow_get_name (ret));
    }
    goto pause_task;
  }

push_failed:
  {
    GST_DEBUG_OBJECT (self, "push flow: %s", gst_flow_get_name (ret));
    if (ret == GST_FLOW_EOS) {
      GST_DEBUG_OBJECT (self, "eos");
      gst_pad_push_event (self->srcpad, gst_event_new_eos ());
    } else if (ret < GST_FLOW_EOS || ret == GST_FLOW_NOT_LINKED) {
      GST_ELEMENT_ERROR (self, STREAM, FAILED,
          ("Internal data stream error."),
          ("streaming stopped, reason: %s", gst_flow_get_name (ret)));
    }
    goto pause_task;
  }

bogus_minmax:
  {
    GST_ELEMENT_ERROR (self, LIBRARY, SETTINGS,
        ("The minimum buffer size is smaller than the maximum buffer size."),
        ("buffer sizes: max=%d, min=%d", self->min, self->max));
    goto pause_task;
  }
}
