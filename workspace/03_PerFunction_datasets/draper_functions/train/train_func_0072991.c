gst_rtspsrc_uri_set_uri (GstURIHandler * handler, const gchar * uri)
{
  GstRTSPSrc *src;
  GstRTSPResult res;
  GstRTSPUrl *newurl = NULL;
  GstSDPMessage *sdp = NULL;

  src = GST_RTSPSRC (handler);


  if (src->conninfo.location && uri && !strcmp (uri, src->conninfo.location))
    goto was_ok;

  if (g_str_has_prefix (uri, "rtsp-sdp://")) {
    if ((res = gst_sdp_message_new (&sdp) < 0))
      goto sdp_failed;

    GST_DEBUG_OBJECT (src, "parsing SDP message");
    if ((res = gst_sdp_message_parse_uri (uri, sdp) < 0))
      goto invalid_sdp;
  } else {

    GST_DEBUG_OBJECT (src, "parsing URI");
    if ((res = gst_rtsp_url_parse (uri, &newurl)) < 0)
      goto parse_error;
  }


  GST_DEBUG_OBJECT (src, "configuring URI");
  g_free (src->conninfo.location);
  src->conninfo.location = g_strdup (uri);
  gst_rtsp_url_free (src->conninfo.url);
  src->conninfo.url = newurl;
  g_free (src->conninfo.url_str);
  if (newurl)
    src->conninfo.url_str = gst_rtsp_url_get_request_uri (src->conninfo.url);
  else
    src->conninfo.url_str = NULL;

  if (src->sdp)
    gst_sdp_message_free (src->sdp);
  src->sdp = sdp;
  src->from_sdp = sdp != NULL;

  GST_DEBUG_OBJECT (src, "set uri: %s", GST_STR_NULL (uri));
  GST_DEBUG_OBJECT (src, "request uri is: %s",
      GST_STR_NULL (src->conninfo.url_str));

  return TRUE;


was_ok:
  {
    GST_DEBUG_OBJECT (src, "URI was ok: '%s'", GST_STR_NULL (uri));
    return TRUE;
  }
sdp_failed:
  {
    GST_ERROR_OBJECT (src, "Could not create new SDP (%d)", res);
    return FALSE;
  }
invalid_sdp:
  {
    GST_ERROR_OBJECT (src, "Not a valid SDP (%d) '%s'", res,
        GST_STR_NULL (uri));
    gst_sdp_message_free (sdp);
    return FALSE;
  }
parse_error:
  {
    GST_ERROR_OBJECT (src, "Not a valid RTSP url '%s' (%d)",
        GST_STR_NULL (uri), res);
    return FALSE;
  }
}
