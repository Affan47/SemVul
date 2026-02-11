gst_base_video_encoder_src_event (GstPad * pad, GstEvent * event)
{
  GstBaseVideoEncoder *base_video_encoder;
  gboolean ret = FALSE;

  base_video_encoder = GST_BASE_VIDEO_ENCODER (gst_pad_get_parent (pad));

  GST_LOG_OBJECT (base_video_encoder, "handling event: %" GST_PTR_FORMAT,
      event);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CUSTOM_UPSTREAM:
    {
      if (gst_video_event_is_force_key_unit (event)) {
        GstClockTime running_time;
        gboolean all_headers;
        guint count;

        if (gst_video_event_parse_upstream_force_key_unit (event,
                &running_time, &all_headers, &count)) {
          ForcedKeyUnitEvent *fevt;

          GST_OBJECT_LOCK (base_video_encoder);
          fevt = forced_key_unit_event_new (running_time, all_headers, count);
          base_video_encoder->force_key_unit =
              g_list_append (base_video_encoder->force_key_unit, fevt);
          GST_OBJECT_UNLOCK (base_video_encoder);

          GST_DEBUG_OBJECT (base_video_encoder,
              "force-key-unit event: running-time %" GST_TIME_FORMAT
              ", all_headers %d, count %u",
              GST_TIME_ARGS (running_time), all_headers, count);
        }
        gst_event_unref (event);
        ret = TRUE;
      } else {
        ret =
            gst_pad_push_event (GST_BASE_VIDEO_CODEC_SINK_PAD
            (base_video_encoder), event);
      }
      break;
    }
    default:
      ret =
          gst_pad_push_event (GST_BASE_VIDEO_CODEC_SINK_PAD
          (base_video_encoder), event);
      break;
  }

  gst_object_unref (base_video_encoder);
  return ret;
}
