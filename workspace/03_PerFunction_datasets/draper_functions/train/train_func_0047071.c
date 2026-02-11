gst_ogg_pad_submit_page (GstOggPad * pad, ogg_page * page)
{
  GstFlowReturn result = GST_FLOW_OK;
  GstOggDemux *ogg;
  gboolean continued = FALSE;

  ogg = pad->ogg;


  if (ogg->segment.rate < 0.0) {
    gint npackets;

    continued = ogg_page_continued (page);


    npackets = ogg_page_packets (page);
    if (!continued) {


      if (npackets == 0)
        npackets = 1;
    }
    GST_LOG_OBJECT (ogg, "continued: %d, %d packets", continued, npackets);

    if (npackets == 0) {
      GST_LOG_OBJECT (ogg, "no decodable packets, we need a previous page");
      goto done;
    }
  }


  if (!ogg->pullmode) {
    result = gst_ogg_pad_handle_push_mode_state (pad, page);
    if (result == GST_FLOW_SKIP_PUSH)
      return GST_FLOW_OK;
    if (result != GST_FLOW_OK)
      return result;
  }

  if (page->header_len + page->body_len > ogg->max_page_size)
    ogg->max_page_size = page->header_len + page->body_len;

  if (ogg_stream_pagein (&pad->map.stream, page) != 0)
    goto choked;


  result = gst_ogg_pad_stream_out (pad, 0);

  if (pad->continued) {
    ogg_packet packet;


    while (pad->continued) {
      ogg_page *p = (ogg_page *) pad->continued->data;

      GST_LOG_OBJECT (ogg, "submitting continued page %p", p);
      if (ogg_stream_pagein (&pad->map.stream, p) != 0)
        goto choked;

      pad->continued = g_list_delete_link (pad->continued, pad->continued);


      gst_ogg_page_free (p);
    }

    GST_LOG_OBJECT (ogg, "flushing last continued packet");

    result = gst_ogg_pad_stream_out (pad, 1);


    while (ogg_stream_packetout (&pad->map.stream, &packet) != 0);
  }

done:

  if (continued) {
    ogg_page *p = gst_ogg_page_copy (page);

    GST_LOG_OBJECT (ogg, "keeping continued page %p", p);
    pad->continued = g_list_prepend (pad->continued, p);
  }

  return result;

choked:
  {
    GST_WARNING_OBJECT (ogg,
        "ogg stream choked on page (serial %08x), "
        "resetting stream", pad->map.serialno);
    gst_ogg_pad_reset (pad);

    return GST_FLOW_OK;
  }
}
