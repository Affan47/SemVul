gst_rtspsrc_setup_auth (GstRTSPSrc * src, GstRTSPMessage * response)
{
  gchar *user = NULL;
  gchar *pass = NULL;
  GstRTSPAuthMethod avail_methods = GST_RTSP_AUTH_NONE;
  GstRTSPAuthMethod method;
  GstRTSPResult auth_result;
  GstRTSPUrl *url;
  GstRTSPConnection *conn;
  gchar *hdr;
  gboolean stale = FALSE;

  conn = src->conninfo.connection;


  if (gst_rtsp_message_get_header (response, GST_RTSP_HDR_WWW_AUTHENTICATE,
          &hdr, 0) == GST_RTSP_OK) {
    gst_rtspsrc_parse_auth_hdr (hdr, &avail_methods, conn, &stale);
  }

  if (avail_methods == GST_RTSP_AUTH_NONE)
    goto no_auth_available;


  if (stale)
    src->tried_url_auth = FALSE;

  url = gst_rtsp_connection_get_url (conn);


  if (url != NULL && !src->tried_url_auth && url->user != NULL
      && url->passwd != NULL) {
    user = url->user;
    pass = url->passwd;
    src->tried_url_auth = TRUE;
    GST_DEBUG_OBJECT (src,
        "Attempting authentication using credentials from the URL");
  } else {
    user = src->user_id;
    pass = src->user_pw;
    GST_DEBUG_OBJECT (src,
        "Attempting authentication using credentials from the properties");
  }


  if (user == NULL || pass == NULL)
    goto no_user_pass;


  for (method = GST_RTSP_AUTH_MAX; method != GST_RTSP_AUTH_NONE; method >>= 1) {

    if ((method & avail_methods) == 0)
      continue;


    auth_result = gst_rtsp_connection_set_auth (conn, method, user, pass);


    if (auth_result == GST_RTSP_OK || auth_result == GST_RTSP_EINVAL) {
      GST_DEBUG_OBJECT (src, "Attempting %s authentication",
          gst_rtsp_auth_method_to_string (method));
      break;
    }
  }

  if (method == GST_RTSP_AUTH_NONE)
    goto no_auth_available;

  return TRUE;

no_auth_available:
  {


    GST_ELEMENT_ERROR (src, RESOURCE, OPEN_READ, (NULL),
        ("No supported authentication protocol was found"));
    return FALSE;
  }
no_user_pass:
  {


    return FALSE;
  }
}
