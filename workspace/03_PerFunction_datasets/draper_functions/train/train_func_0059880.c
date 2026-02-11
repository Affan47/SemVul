encodebin_element_added (GstElement * encodebin, GstElement * new_element,
    GstCameraBin2 * camera)
{
  GstElementFactory *factory = gst_element_get_factory (new_element);

  if (factory != NULL) {
    if (strcmp (GST_OBJECT_NAME (factory), "audiorate") == 0 ||
        strcmp (GST_OBJECT_NAME (factory), "videorate") == 0) {
      g_object_set (new_element, "skip-to-first", TRUE, NULL);
    }
  }

  if (GST_IS_TAG_SETTER (new_element)) {
    GstTagSetter *tagsetter = GST_TAG_SETTER (new_element);

    gst_tag_setter_set_tag_merge_mode (tagsetter, GST_TAG_MERGE_REPLACE);
  }
}
