gst_rtp_ssrc_demux_chain (GstPad * pad, GstBuffer * buf)
{
  GstFlowReturn ret;
  GstRtpSsrcDemux *demux;
  guint32 ssrc;
  GstRtpSsrcDemuxPad *dpad;
  GstPad *srcpad;

  demux = GST_RTP_SSRC_DEMUX (GST_OBJECT_PARENT (pad));

  if (!gst_rtp_buffer_validate (buf))
    goto invalid_payload;

  ssrc = gst_rtp_buffer_get_ssrc (buf);

  GST_DEBUG_OBJECT (demux, "received buffer of SSRC %08x", ssrc);

  GST_PAD_LOCK (demux);
  dpad = find_or_create_demux_pad_for_ssrc (demux, ssrc);
  if (dpad == NULL) {
    GST_PAD_UNLOCK (demux);
    goto create_failed;
  }
  srcpad = gst_object_ref (dpad->rtp_pad);
  GST_PAD_UNLOCK (demux);


  ret = gst_pad_push (srcpad, buf);

  gst_object_unref (srcpad);

  return ret;


invalid_payload:
  {

    GST_ELEMENT_ERROR (demux, STREAM, DECODE, (NULL),
        ("Dropping invalid RTP payload"));
    gst_buffer_unref (buf);
    return GST_FLOW_ERROR;
  }
create_failed:
  {
    GST_ELEMENT_ERROR (demux, STREAM, DECODE, (NULL),
        ("Could not create new pad"));
    gst_buffer_unref (buf);
    return GST_FLOW_ERROR;
  }
}
