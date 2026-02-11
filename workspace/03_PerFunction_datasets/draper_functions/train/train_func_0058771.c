gst_mpdparser_parse_content_component_node (GList ** list, xmlNode * a_node)
{
  xmlNode *cur_node;
  GstContentComponentNode *new_content_component;

  new_content_component = g_slice_new0 (GstContentComponentNode);
  if (new_content_component == NULL) {
    GST_WARNING ("Allocation of ContentComponent node failed!");
    return;
  }
  *list = g_list_append (*list, new_content_component);

  GST_LOG ("attributes of ContentComponent node:");
  gst_mpdparser_get_xml_prop_unsigned_integer (a_node, "id", 0,
      &new_content_component->id);
  gst_mpdparser_get_xml_prop_string (a_node, "lang",
      &new_content_component->lang);
  gst_mpdparser_get_xml_prop_string (a_node, "contentType",
      &new_content_component->contentType);
  gst_mpdparser_get_xml_prop_ratio (a_node, "par", &new_content_component->par);


  for (cur_node = a_node->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrcmp (cur_node->name, (xmlChar *) "Accessibility") == 0) {
        gst_mpdparser_parse_descriptor_type_node
            (&new_content_component->Accessibility, cur_node);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "Role") == 0) {
        gst_mpdparser_parse_descriptor_type_node (&new_content_component->Role,
            cur_node);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "Rating") == 0) {
        gst_mpdparser_parse_descriptor_type_node
            (&new_content_component->Rating, cur_node);
      } else if (xmlStrcmp (cur_node->name, (xmlChar *) "Viewpoint") == 0) {
        gst_mpdparser_parse_descriptor_type_node
            (&new_content_component->Viewpoint, cur_node);
      }
    }
  }
}
