gst_pixbufscale_transform_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps)
{
  GstCaps *ret;
  int i;

  ret = gst_caps_copy (caps);

  for (i = 0; i < gst_caps_get_size (ret); i++) {
    GstStructure *structure = gst_caps_get_structure (ret, i);

    gst_structure_set (structure,
        "width", GST_TYPE_INT_RANGE, 16, 4096,
        "height", GST_TYPE_INT_RANGE, 16, 4096, NULL);
    gst_structure_remove_field (structure, "pixel-aspect-ratio");
  }

  GST_DEBUG_OBJECT (trans, "returning caps: %" GST_PTR_FORMAT, ret);
  return ret;
}
