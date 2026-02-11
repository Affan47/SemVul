gst_dvbsub_overlay_setcaps_video (GstPad * pad, GstCaps * caps)
{
  GstDVBSubOverlay *render = GST_DVBSUB_OVERLAY (gst_pad_get_parent (pad));
  gboolean ret = FALSE;
  GstVideoInfo info;

  if (!gst_video_info_from_caps (&info, caps))
    goto invalid_caps;

  render->info = info;

  ret = gst_pad_set_caps (render->srcpad, caps);
  if (!ret)
    goto out;

  gst_dvbsub_overlay_negotiate (render);

  GST_DEBUG_OBJECT (render, "ass renderer setup complete");

out:
  gst_object_unref (render);

  return ret;


invalid_caps:
  {
    GST_ERROR_OBJECT (render, "Can't parse caps: %" GST_PTR_FORMAT, caps);
    ret = FALSE;
    goto out;
  }
}
