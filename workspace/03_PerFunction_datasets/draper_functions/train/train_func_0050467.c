gst_rtspsrc_stream_configure_transport (GstRTSPStream * stream,
    GstRTSPTransport * transport)
{
  GstRTSPSrc *src;
  GstPad *outpad = NULL;
  GstPadTemplate *template;
  gchar *name;
  GstStructure *s;
  const gchar *mime;

  src = stream->parent;

  GST_DEBUG_OBJECT (src, "configuring transport for stream %p", stream);

  s = gst_caps_get_structure (stream->caps, 0);


  if (gst_rtsp_transport_get_mime (transport->trans, &mime) < 0)
    goto unknown_transport;
  if (!mime)
    goto unknown_transport;


  GST_DEBUG_OBJECT (src, "setting mime to %s", mime);
  gst_structure_set_name (s, mime);


  if (!gst_rtspsrc_stream_configure_manager (src, stream, transport))
    goto no_manager;

  switch (transport->lower_transport) {
    case GST_RTSP_LOWER_TRANS_TCP:
      if (!gst_rtspsrc_stream_configure_tcp (src, stream, transport, &outpad))
        goto transport_failed;
      break;
    case GST_RTSP_LOWER_TRANS_UDP_MCAST:
      if (!gst_rtspsrc_stream_configure_mcast (src, stream, transport, &outpad))
        goto transport_failed;

    case GST_RTSP_LOWER_TRANS_UDP:
      if (!gst_rtspsrc_stream_configure_udp (src, stream, transport, &outpad))
        goto transport_failed;


      if (!gst_rtspsrc_stream_configure_udp_sinks (src, stream, transport))
        goto transport_failed;
      break;
    default:
      goto unknown_transport;
  }

  if (outpad) {
    GST_DEBUG_OBJECT (src, "creating ghostpad");

    gst_pad_use_fixed_caps (outpad);


    name = g_strdup_printf ("stream_%u", stream->id);
    template = gst_static_pad_template_get (&rtptemplate);
    stream->srcpad = gst_ghost_pad_new_from_template (name, outpad, template);
    gst_pad_set_event_function (stream->srcpad, gst_rtspsrc_handle_src_event);
    gst_pad_set_query_function (stream->srcpad, gst_rtspsrc_handle_src_query);
    gst_object_unref (template);
    g_free (name);

    gst_object_unref (outpad);
  }

  stream->last_ret = GST_FLOW_OK;

  return TRUE;


transport_failed:
  {
    GST_DEBUG_OBJECT (src, "failed to configure transport");
    return FALSE;
  }
unknown_transport:
  {
    GST_DEBUG_OBJECT (src, "unknown transport");
    return FALSE;
  }
no_manager:
  {
    GST_DEBUG_OBJECT (src, "cannot get a session manager");
    return FALSE;
  }
}
