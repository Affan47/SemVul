gst_rsvg_overlay_set_caps (GstBaseTransform * btrans, GstCaps * incaps,
    GstCaps * outcaps)
{
  GstRsvgOverlay *overlay = GST_RSVG_OVERLAY (btrans);

  return G_LIKELY (gst_video_format_parse_caps (incaps,
          &overlay->caps_format, &overlay->caps_width, &overlay->caps_height));
}
