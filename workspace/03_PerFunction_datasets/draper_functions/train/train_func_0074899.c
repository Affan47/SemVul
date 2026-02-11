gst_element_found_tags_for_pad (GstElement * element,
    GstPad * pad, GstTagList * list)
{
  g_return_if_fail (element != NULL);
  g_return_if_fail (pad != NULL);
  g_return_if_fail (list != NULL);

  gst_pad_push_event (pad, gst_event_new_tag (gst_tag_list_copy (list)));

  gst_element_post_message (element,
      gst_message_new_tag_full (GST_OBJECT (element), pad, list));
}
