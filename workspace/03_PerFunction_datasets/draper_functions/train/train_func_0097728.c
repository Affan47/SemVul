gst_dvbsub_overlay_setcaps_video (GstPad * pad, GstCaps * caps)
{
  GstDVBSubOverlay *render = GST_DVBSUB_OVERLAY (gst_pad_get_parent (pad));
  gboolean ret = FALSE;

  render->width = 0;
  render->height = 0;

  if (!gst_video_format_parse_caps (caps, &render->format, &render->width,
          &render->height) ||
      !gst_video_parse_caps_framerate (caps, &render->fps_n, &render->fps_d)) {
    GST_ERROR_OBJECT (render, "Can't parse caps: %" GST_PTR_FORMAT, caps);
    ret = FALSE;
    goto out;
  }

  gst_video_parse_caps_pixel_aspect_ratio (caps, &render->par_n,
      &render->par_d);

  ret = gst_pad_set_caps (render->srcpad, caps);
  if (!ret)
    goto out;

  GST_DEBUG_OBJECT (render, "ass renderer setup complete");

out:
  gst_object_unref (render);

  return ret;
}
