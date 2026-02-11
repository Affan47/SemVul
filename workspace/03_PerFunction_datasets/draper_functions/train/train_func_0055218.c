gst_play_sink_request_new_pad (GstElement * element, GstPadTemplate * templ,
    const gchar * name, const GstCaps * caps)
{
  GstPlaySink *psink;
  GstPad *pad;
  GstPlaySinkType type;
  const gchar *tplname;

  g_return_val_if_fail (templ != NULL, NULL);

  GST_DEBUG_OBJECT (element, "name:%s", name);

  psink = GST_PLAY_SINK (element);
  tplname = GST_PAD_TEMPLATE_NAME_TEMPLATE (templ);


  if (!strcmp (tplname, "audio_sink"))
    type = GST_PLAY_SINK_TYPE_AUDIO;
  else if (!strcmp (tplname, "audio_raw_sink"))
    type = GST_PLAY_SINK_TYPE_AUDIO_RAW;
  else if (!strcmp (tplname, "video_sink"))
    type = GST_PLAY_SINK_TYPE_VIDEO;
  else if (!strcmp (tplname, "video_raw_sink"))
    type = GST_PLAY_SINK_TYPE_VIDEO_RAW;
  else if (!strcmp (tplname, "text_sink"))
    type = GST_PLAY_SINK_TYPE_TEXT;
  else
    goto unknown_template;

  pad = gst_play_sink_request_pad (psink, type);
  return pad;

unknown_template:
  GST_WARNING_OBJECT (element, "Unknown pad template");
  return NULL;
}
