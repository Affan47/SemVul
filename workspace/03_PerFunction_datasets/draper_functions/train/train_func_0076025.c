gst_rtsp_media_factory_collect_streams (GstRTSPMediaFactory * factory,
    const GstRTSPUrl * url, GstRTSPMedia * media)
{
  GstElement *element, *elem;
  GstPad *pad;
  gint i;
  GstRTSPMediaStream *stream;
  gboolean have_elem;

  element = media->element;

  have_elem = TRUE;
  for (i = 0; have_elem; i++) {
    gchar *name;

    have_elem = FALSE;

    name = g_strdup_printf ("pay%d", i);
    if ((elem = gst_bin_get_by_name (GST_BIN (element), name))) {

      stream = g_new0 (GstRTSPMediaStream, 1);
      stream->payloader = elem;

      GST_INFO ("found stream %d with payloader %p", i, elem);

      pad = gst_element_get_static_pad (elem, "src");


      stream->srcpad = gst_ghost_pad_new (name, pad);
      gst_pad_set_active (stream->srcpad, TRUE);
      gst_element_add_pad (media->element, stream->srcpad);
      gst_object_unref (elem);


      g_array_append_val (media->streams, stream);
      have_elem = TRUE;
    }
    g_free (name);

    name = g_strdup_printf ("dynpay%d", i);
    if ((elem = gst_bin_get_by_name (GST_BIN (element), name))) {


      GST_INFO ("found dynamic element %d, %p", i, elem);

      media->dynamic = g_list_prepend (media->dynamic, elem);

      have_elem = TRUE;
    }
    g_free (name);
  }
}
