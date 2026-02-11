gst_vp8_enc_sink_event (GstBaseVideoEncoder * benc, GstEvent * event)
{
  GstVP8Enc *enc = GST_VP8_ENC (benc);

  if (GST_EVENT_TYPE (event) == GST_EVENT_TAG) {
    GstTagList *list;
    GstTagSetter *setter = GST_TAG_SETTER (enc);
    const GstTagMergeMode mode = gst_tag_setter_get_tag_merge_mode (setter);

    gst_event_parse_tag (event, &list);
    gst_tag_setter_merge_tags (setter, list, mode);
  }


  return FALSE;
}
