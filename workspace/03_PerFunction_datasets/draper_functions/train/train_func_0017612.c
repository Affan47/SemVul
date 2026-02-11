create_send_rtp (GstRtpBin * rtpbin, GstPadTemplate * templ, const gchar * name)
{
  gchar *gname;
  guint sessid;
  GstRtpBinSession *session;
  GstElementClass *klass;


  if (name == NULL || sscanf (name, "send_rtp_sink_%u", &sessid) != 1)
    goto no_name;


  session = find_session_by_id (rtpbin, sessid);
  if (!session) {

    session = create_session (rtpbin, sessid);
    if (session == NULL)
      goto create_error;
  }


  if (session->send_rtp_sink_ghost != NULL)
    return session->send_rtp_sink_ghost;


  session->send_rtp_sink =
      gst_element_get_request_pad (session->session, "send_rtp_sink");
  if (session->send_rtp_sink == NULL)
    goto pad_failed;

  session->send_rtp_sink_ghost =
      gst_ghost_pad_new_from_template (name, session->send_rtp_sink, templ);
  gst_pad_set_active (session->send_rtp_sink_ghost, TRUE);
  gst_element_add_pad (GST_ELEMENT_CAST (rtpbin), session->send_rtp_sink_ghost);


  session->send_rtp_src =
      gst_element_get_static_pad (session->session, "send_rtp_src");
  if (session->send_rtp_src == NULL)
    goto no_srcpad;


  klass = GST_ELEMENT_GET_CLASS (rtpbin);
  gname = g_strdup_printf ("send_rtp_src_%u", sessid);
  templ = gst_element_class_get_pad_template (klass, "send_rtp_src_%u");
  session->send_rtp_src_ghost =
      gst_ghost_pad_new_from_template (gname, session->send_rtp_src, templ);
  gst_pad_set_active (session->send_rtp_src_ghost, TRUE);
  gst_element_add_pad (GST_ELEMENT_CAST (rtpbin), session->send_rtp_src_ghost);
  g_free (gname);

  return session->send_rtp_sink_ghost;


no_name:
  {
    g_warning ("rtpbin: invalid name given");
    return NULL;
  }
create_error:
  {

    return NULL;
  }
pad_failed:
  {
    g_warning ("rtpbin: failed to get session pad for session %d", sessid);
    return NULL;
  }
no_srcpad:
  {
    g_warning ("rtpbin: failed to get rtp source pad for session %d", sessid);
    return NULL;
  }
}
