gst_mpdparser_parse_period_node (GList ** list, xmlNode * a_node)
{
  xmlNode *cur_node;
  GstPeriodNode *new_period;

  new_period = g_slice_new0 (GstPeriodNode);
  if (new_period == NULL) {
    GST_WARNING ("Allocation of Period node failed!");
    return;
  }
  *list = g_list_append (*list, new_period);

  new_period->start = GST_CLOCK_TIME_NONE;

  GST_LOG ("attributes of Period node:");
  gst_mpdparser_get_xml_prop_string (a_node, "id", &new_period->id);
  gst_mpdparser_get_xml_prop_duration (a_node, "start", -1, &new_period->start);
  gst_mpdparser_get_xml_prop_duration (a_node, "duration", -1,
      &new_period->duration);
  gst_mpdparser_get_xml_prop_boolean (a_node, "bitstreamSwitching",
      FALSE, &new_period->bitstreamSwitching);


  for (cur_node = a_node->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrcmp (cur_node->name, (xmlChar *) "SegmentBase") == 0) {
        gst_mpdparser_parse_seg_base_type_ext (&new_period->SegmentBase,
            cur_node, NULL);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "SegmentList") == 0) {
        gst_mpdparser_parse_segment_list_node (&new_period->SegmentList,
            cur_node, NULL);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "SegmentTemplate") == 0) {
        gst_mpdparser_parse_segment_template_node (&new_period->SegmentTemplate,
            cur_node, NULL);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "Subset") == 0) {
        gst_mpdparser_parse_subset_node (&new_period->Subsets, cur_node);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "BaseURL") == 0) {
        gst_mpdparser_parse_baseURL_node (&new_period->BaseURLs, cur_node);
      }
    }
  }


  for (cur_node = a_node->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrcmp (cur_node->name, (xmlChar *) "AdaptationSet") == 0) {
        gst_mpdparser_parse_adaptation_set_node (&new_period->AdaptationSets,
            cur_node, new_period);
      }
    }
  }
}
