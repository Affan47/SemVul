gst_matroska_read_common_found_global_tag (GstMatroskaReadCommon * common,
    GstElement * el, GstTagList * taglist)
{
  if (common->global_tags) {

    gst_tag_list_insert (common->global_tags, taglist, GST_TAG_MERGE_APPEND);
    gst_tag_list_free (taglist);
  } else {

    GST_DEBUG_OBJECT (common, "Sending late global tags %" GST_PTR_FORMAT,
        taglist);
    gst_element_found_tags (el, taglist);
  }
}
