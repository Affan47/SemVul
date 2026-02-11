gst_video_flip_transform_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps)
{
  GstVideoFlip *videoflip = GST_VIDEO_FLIP (trans);
  GstCaps *ret;
  gint width, height, i;

  ret = gst_caps_copy (caps);

  for (i = 0; i < gst_caps_get_size (ret); i++) {
    GstStructure *structure = gst_caps_get_structure (ret, i);
    gint par_n, par_d;

    if (gst_structure_get_int (structure, "width", &width) &&
        gst_structure_get_int (structure, "height", &height)) {

      switch (videoflip->method) {
        case GST_VIDEO_FLIP_METHOD_90R:
        case GST_VIDEO_FLIP_METHOD_90L:
        case GST_VIDEO_FLIP_METHOD_TRANS:
        case GST_VIDEO_FLIP_METHOD_OTHER:
          gst_structure_set (structure, "width", G_TYPE_INT, height,
              "height", G_TYPE_INT, width, NULL);
          if (gst_structure_get_fraction (structure, "pixel-aspect-ratio",
                  &par_n, &par_d)) {
            if (par_n != 1 || par_d != 1) {
              GValue val = { 0, };

              g_value_init (&val, GST_TYPE_FRACTION);
              gst_value_set_fraction (&val, par_d, par_n);
              gst_structure_set_value (structure, "pixel-aspect-ratio", &val);
              g_value_unset (&val);
            }
          }
          break;
        case GST_VIDEO_FLIP_METHOD_IDENTITY:
        case GST_VIDEO_FLIP_METHOD_180:
        case GST_VIDEO_FLIP_METHOD_HORIZ:
        case GST_VIDEO_FLIP_METHOD_VERT:
          gst_structure_set (structure, "width", G_TYPE_INT, width,
              "height", G_TYPE_INT, height, NULL);
          break;
        default:
          g_assert_not_reached ();
          break;
      }
    }
  }

  GST_DEBUG_OBJECT (videoflip, "transformed %" GST_PTR_FORMAT " to %"
      GST_PTR_FORMAT, caps, ret);

  return ret;
}
