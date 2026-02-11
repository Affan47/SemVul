gst_smokeenc_setcaps (GstPad * pad, GstCaps * caps)
{
  GstSmokeEnc *smokeenc;
  GstStructure *structure;
  const GValue *framerate;
  gboolean ret;
  GstCaps *srccaps;

  smokeenc = GST_SMOKEENC (gst_pad_get_parent (pad));

  structure = gst_caps_get_structure (caps, 0);
  framerate = gst_structure_get_value (structure, "framerate");
  if (framerate) {
    smokeenc->fps_num = gst_value_get_fraction_numerator (framerate);
    smokeenc->fps_denom = gst_value_get_fraction_denominator (framerate);
  } else {
    smokeenc->fps_num = 0;
    smokeenc->fps_denom = 1;
  }

  gst_structure_get_int (structure, "width", &smokeenc->width);
  gst_structure_get_int (structure, "height", &smokeenc->height);

  if ((smokeenc->width & 0x0f) != 0 || (smokeenc->height & 0x0f) != 0)
    goto width_or_height_notx16;

  if (!gst_smokeenc_resync (smokeenc))
    goto init_failed;

  srccaps = gst_caps_new_simple ("video/x-smoke",
      "width", G_TYPE_INT, smokeenc->width,
      "height", G_TYPE_INT, smokeenc->height,
      "framerate", GST_TYPE_FRACTION, smokeenc->fps_num, smokeenc->fps_denom,
      NULL);

  ret = gst_pad_set_caps (smokeenc->srcpad, srccaps);
  gst_caps_unref (srccaps);

  gst_object_unref (smokeenc);

  return ret;

width_or_height_notx16:
  {
    GST_WARNING_OBJECT (smokeenc, "width and height must be multiples of 16"
        ", %dx%d not allowed", smokeenc->width, smokeenc->height);
    gst_object_unref (smokeenc);
    return FALSE;
  }
init_failed:
  {
    GST_WARNING_OBJECT (smokeenc, "could not init decoder");
    gst_object_unref (smokeenc);
    return FALSE;
  }
}
