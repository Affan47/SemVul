gst_rtspsrc_reconnect (GstRTSPSrc * src, gboolean async)
{
  GstRTSPResult res = GST_RTSP_OK;
  gboolean restart;

  GST_DEBUG_OBJECT (src, "doing reconnect");

  GST_OBJECT_LOCK (src);


  restart = src->need_activate;
  GST_OBJECT_UNLOCK (src);


  if (!restart)
    goto done;


  src->cur_protocols = GST_RTSP_LOWER_TRANS_TCP;


  if ((res = gst_rtspsrc_close (src, async, FALSE)) < 0)
    goto done;


  if (!(src->protocols & GST_RTSP_LOWER_TRANS_TCP) || src->from_sdp)
    goto no_protocols;


  GST_ELEMENT_WARNING (src, RESOURCE, READ, (NULL),
      ("Could not receive any UDP packets for %.4f seconds, maybe your "
          "firewall is blocking it. Retrying using a TCP connection.",
          gst_guint64_to_gdouble (src->udp_timeout / 1000000.0)));


  if (gst_rtspsrc_open (src, async) < 0)
    goto open_failed;


  if (gst_rtspsrc_play (src, &src->segment, async) < 0)
    goto play_failed;

done:
  return res;


no_protocols:
  {
    src->cur_protocols = 0;

    GST_ELEMENT_ERROR (src, RESOURCE, READ, (NULL),
        ("Could not receive any UDP packets for %.4f seconds, maybe your "
            "firewall is blocking it. No other protocols to try.",
            gst_guint64_to_gdouble (src->udp_timeout / 1000000.0)));
    return GST_RTSP_ERROR;
  }
open_failed:
  {
    GST_DEBUG_OBJECT (src, "open failed");
    return GST_RTSP_OK;
  }
play_failed:
  {
    GST_DEBUG_OBJECT (src, "play failed");
    return GST_RTSP_OK;
  }
}
