gst_video_crop_transform_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps)
{
  GstVideoCrop *vcrop;
  GstCaps *other_caps;
  gint dy, dx, i;

  vcrop = GST_VIDEO_CROP (trans);

  GST_OBJECT_LOCK (vcrop);

  GST_LOG_OBJECT (vcrop, "l=%d,r=%d,b=%d,t=%d",
      vcrop->crop_left, vcrop->crop_right, vcrop->crop_bottom, vcrop->crop_top);

  if (direction == GST_PAD_SRC) {
    dx = vcrop->crop_left + vcrop->crop_right;
    dy = vcrop->crop_top + vcrop->crop_bottom;
  } else {
    dx = 0 - (vcrop->crop_left + vcrop->crop_right);
    dy = 0 - (vcrop->crop_top + vcrop->crop_bottom);
  }
  GST_OBJECT_UNLOCK (vcrop);

  GST_LOG_OBJECT (vcrop, "transforming caps %" GST_PTR_FORMAT, caps);

  other_caps = gst_caps_new_empty ();

  for (i = 0; i < gst_caps_get_size (caps); ++i) {
    const GValue *v;
    GstStructure *structure, *new_structure;
    GValue w_val = { 0, }, h_val = {
    0,};

    structure = gst_caps_get_structure (caps, i);

    v = gst_structure_get_value (structure, "width");
    if (!gst_video_crop_transform_dimension_value (v, dx, &w_val)) {
      GST_WARNING_OBJECT (vcrop, "could not tranform width value with dx=%d"
          ", caps structure=%" GST_PTR_FORMAT, dx, structure);
      continue;
    }

    v = gst_structure_get_value (structure, "height");
    if (!gst_video_crop_transform_dimension_value (v, dy, &h_val)) {
      g_value_unset (&w_val);
      GST_WARNING_OBJECT (vcrop, "could not tranform height value with dy=%d"
          ", caps structure=%" GST_PTR_FORMAT, dy, structure);
      continue;
    }

    new_structure = gst_structure_copy (structure);
    gst_structure_set_value (new_structure, "width", &w_val);
    gst_structure_set_value (new_structure, "height", &h_val);
    g_value_unset (&w_val);
    g_value_unset (&h_val);
    GST_LOG_OBJECT (vcrop, "transformed structure %2d: %" GST_PTR_FORMAT
        " => %" GST_PTR_FORMAT, i, structure, new_structure);
    gst_caps_append_structure (other_caps, new_structure);
  }

  if (gst_caps_is_empty (other_caps)) {
    gst_caps_unref (other_caps);
    other_caps = NULL;
  }

  return other_caps;
}
