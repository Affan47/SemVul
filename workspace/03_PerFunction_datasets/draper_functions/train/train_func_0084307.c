theora_enc_src_event (GstPad * pad, GstEvent * event)
{
  GstTheoraEnc *enc;
  gboolean res = TRUE;

  enc = GST_THEORA_ENC (GST_PAD_PARENT (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CUSTOM_UPSTREAM:
    {
      const GstStructure *s;

      s = gst_event_get_structure (event);

      if (gst_structure_has_name (s, "GstForceKeyUnit")) {
        GST_OBJECT_LOCK (enc);
        enc->force_keyframe = TRUE;
        GST_OBJECT_UNLOCK (enc);

        res = TRUE;
        gst_event_unref (event);
      } else {
        res = gst_pad_push_event (enc->sinkpad, event);
      }
      break;
    }
    default:
      res = gst_pad_push_event (enc->sinkpad, event);
      break;
  }

  return res;
}
