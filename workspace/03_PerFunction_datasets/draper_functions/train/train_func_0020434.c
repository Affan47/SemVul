gst_mpdparser_parse_segment_timeline_node (GstSegmentTimelineNode ** pointer,
    xmlNode * a_node)
{
  xmlNode *cur_node;
  GstSegmentTimelineNode *new_seg_timeline;

  gst_mpdparser_free_segment_timeline_node (*pointer);
  *pointer = new_seg_timeline = gst_mpdparser_segment_timeline_node_new ();
  if (new_seg_timeline == NULL) {
    GST_WARNING ("Allocation of SegmentTimeline node failed!");
    return;
  }


  for (cur_node = a_node->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrcmp (cur_node->name, (xmlChar *) "S") == 0) {
        gst_mpdparser_parse_s_node (&new_seg_timeline->S, cur_node);
      }
    }
  }
}
