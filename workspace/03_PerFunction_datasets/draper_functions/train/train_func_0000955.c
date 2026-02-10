gst_aspect_ratio_crop_transform_caps (GstAspectRatioCrop * aspect_ratio_crop,
    GstCaps * caps)
{
  GstCaps *transform;
  gint size, i;

  transform = gst_caps_new_empty ();

  size = gst_caps_get_size (caps);

  for (i = 0; i < size; i++) {
    GstStructure *s;
    GstStructure *trans_s;

    s = gst_caps_get_structure (caps, i);

    gst_aspect_ratio_transform_structure (aspect_ratio_crop, s, &trans_s,
        FALSE);
    gst_caps_append_structure (transform, trans_s);
  }

  return transform;
}
