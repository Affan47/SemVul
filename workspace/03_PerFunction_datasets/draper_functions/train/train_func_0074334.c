gst_asf_mux_get_headers_size (GstAsfMux * asfmux)
{
  GSList *walk;
  gint stream_num = 0;
  guint size = ASF_HEADER_OBJECT_SIZE +
      ASF_FILE_PROPERTIES_OBJECT_SIZE + ASF_HEADER_EXTENSION_OBJECT_SIZE;


  for (walk = asfmux->collect->data; walk; walk = g_slist_next (walk)) {
    GstAsfPad *asfpad = (GstAsfPad *) walk->data;

    if (asfpad->is_audio)
      size += ASF_AUDIO_SPECIFIC_DATA_SIZE;
    else
      size += ASF_VIDEO_SPECIFIC_DATA_SIZE;

    if (asfpad->codec_data)
      size += GST_BUFFER_SIZE (asfpad->codec_data);

    stream_num++;
  }
  size += stream_num * (ASF_STREAM_PROPERTIES_OBJECT_SIZE +
      ASF_EXTENDED_STREAM_PROPERTIES_OBJECT_SIZE);

  return size;
}
