gst_mpeg4vparse_pre_push_frame (GstBaseParse * parse, GstBaseParseFrame * frame)
{
  GstMpeg4VParse *mp4vparse = GST_MPEG4VIDEO_PARSE (parse);
  GstBuffer *buffer = frame->buffer;
  gboolean push_codec = FALSE;
  GstEvent *event = NULL;

  if ((event = check_pending_key_unit_event (mp4vparse->force_key_unit_event,
              &parse->segment, GST_BUFFER_TIMESTAMP (buffer),
              GST_BUFFER_FLAGS (buffer), mp4vparse->pending_key_unit_ts))) {
    gst_mpeg4vparse_prepare_key_unit (mp4vparse, event);
    push_codec = TRUE;
  }


  if (mp4vparse->interval > 0 || push_codec) {
    GstClockTime timestamp = GST_BUFFER_TIMESTAMP (buffer);
    guint64 diff;


    if (!GST_CLOCK_TIME_IS_VALID (mp4vparse->last_report)) {
      mp4vparse->last_report = timestamp;
    }

    if (!GST_BUFFER_FLAG_IS_SET (buffer, GST_BUFFER_FLAG_DELTA_UNIT)) {
      if (timestamp > mp4vparse->last_report)
        diff = timestamp - mp4vparse->last_report;
      else
        diff = 0;

      GST_LOG_OBJECT (mp4vparse,
          "now %" GST_TIME_FORMAT ", last config %" GST_TIME_FORMAT,
          GST_TIME_ARGS (timestamp), GST_TIME_ARGS (mp4vparse->last_report));

      GST_LOG_OBJECT (mp4vparse,
          "interval since last config %" GST_TIME_FORMAT, GST_TIME_ARGS (diff));

      if (GST_TIME_AS_SECONDS (diff) >= mp4vparse->interval || push_codec) {
        GstMapInfo cmap;
        gsize csize;
        gboolean diffconf;


        GST_INFO_OBJECT (parse, "inserting config in stream");
        gst_buffer_map (mp4vparse->config, &cmap, GST_MAP_READ);
        diffconf = (gst_buffer_get_size (buffer) < cmap.size)
            || gst_buffer_memcmp (buffer, 0, cmap.data, cmap.size);
        csize = cmap.size;
        gst_buffer_unmap (mp4vparse->config, &cmap);


        if (diffconf) {
          GstBuffer *superbuf;


          superbuf =
              gst_buffer_append (gst_buffer_ref (mp4vparse->config),
              gst_buffer_ref (buffer));
          gst_buffer_copy_into (superbuf, buffer, GST_BUFFER_COPY_METADATA, 0,
              csize);
          gst_buffer_replace (&frame->out_buffer, superbuf);
          gst_buffer_unref (superbuf);
        } else {
          GST_INFO_OBJECT (parse, "... but avoiding duplication");
        }

        if (G_UNLIKELY (timestamp != -1)) {
          mp4vparse->last_report = timestamp;
        }
      }
    }
  }

  return GST_FLOW_OK;
}
