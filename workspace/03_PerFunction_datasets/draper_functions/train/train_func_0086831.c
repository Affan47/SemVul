gst_mpdparser_parse_root_node (GstMPDNode ** pointer, xmlNode * a_node)
{
  xmlNode *cur_node;
  GstMPDNode *new_mpd;

  gst_mpdparser_free_mpd_node (*pointer);
  *pointer = new_mpd = g_slice_new0 (GstMPDNode);
  if (new_mpd == NULL) {
    GST_WARNING ("Allocation of MPD node failed!");
    return;
  }

  GST_LOG ("namespaces of root MPD node:");
  new_mpd->default_namespace =
      gst_mpdparser_get_xml_node_namespace (a_node, NULL);
  new_mpd->namespace_xsi = gst_mpdparser_get_xml_node_namespace (a_node, "xsi");
  new_mpd->namespace_ext = gst_mpdparser_get_xml_node_namespace (a_node, "ext");

  GST_LOG ("attributes of root MPD node:");
  gst_mpdparser_get_xml_prop_string (a_node, "schemaLocation",
      &new_mpd->schemaLocation);
  gst_mpdparser_get_xml_prop_string (a_node, "id", &new_mpd->id);
  gst_mpdparser_get_xml_prop_string (a_node, "profiles", &new_mpd->profiles);
  gst_mpdparser_get_xml_prop_type (a_node, "type", &new_mpd->type);
  gst_mpdparser_get_xml_prop_dateTime (a_node, "availabilityStartTime",
      &new_mpd->availabilityStartTime);
  gst_mpdparser_get_xml_prop_dateTime (a_node, "availabilityEndTime",
      &new_mpd->availabilityEndTime);
  gst_mpdparser_get_xml_prop_duration (a_node, "mediaPresentationDuration", -1,
      &new_mpd->mediaPresentationDuration);
  gst_mpdparser_get_xml_prop_duration (a_node, "minimumUpdatePeriod", -1,
      &new_mpd->minimumUpdatePeriod);
  gst_mpdparser_get_xml_prop_duration (a_node, "minBufferTime", -1,
      &new_mpd->minBufferTime);
  gst_mpdparser_get_xml_prop_duration (a_node, "timeShiftBufferDepth", -1,
      &new_mpd->timeShiftBufferDepth);
  gst_mpdparser_get_xml_prop_duration (a_node, "suggestedPresentationDelay", -1,
      &new_mpd->suggestedPresentationDelay);
  gst_mpdparser_get_xml_prop_duration (a_node, "maxSegmentDuration", -1,
      &new_mpd->maxSegmentDuration);
  gst_mpdparser_get_xml_prop_duration (a_node, "maxSubsegmentDuration", -1,
      &new_mpd->maxSubsegmentDuration);


  for (cur_node = a_node->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrcmp (cur_node->name, (xmlChar *) "Period") == 0) {
        gst_mpdparser_parse_period_node (&new_mpd->Periods, cur_node);
      } else if (xmlStrcmp (cur_node->name,
              (xmlChar *) "ProgramInformation") == 0) {
        gst_mpdparser_parse_program_info_node (&new_mpd->ProgramInfo, cur_node);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "BaseURL") == 0) {
        gst_mpdparser_parse_baseURL_node (&new_mpd->BaseURLs, cur_node);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "Location") == 0) {
        gst_mpdparser_parse_location_node (&new_mpd->Locations, cur_node);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "Metrics") == 0) {
        gst_mpdparser_parse_metrics_node (&new_mpd->Metrics, cur_node);
      }
    }
  }
}
