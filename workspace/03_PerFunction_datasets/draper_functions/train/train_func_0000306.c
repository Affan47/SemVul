mpegpsmux_create_streams (MpegPsMux * mux)
{


  GstFlowReturn ret = GST_FLOW_OK;
  GSList *walk = mux->collect->data;


  while (walk) {
    GstCollectData *c_data = (GstCollectData *) walk->data;
    MpegPsPadData *ps_data = (MpegPsPadData *) walk->data;

    walk = g_slist_next (walk);

    if (ps_data->stream == NULL) {
      ret = mpegpsmux_create_stream (mux, ps_data, c_data->pad);
      if (ret != GST_FLOW_OK)
        goto no_stream;
    }
  }

  return GST_FLOW_OK;
no_stream:
  GST_ELEMENT_ERROR (mux, STREAM, MUX,
      ("Could not create handler for stream"), (NULL));
  return ret;
}
