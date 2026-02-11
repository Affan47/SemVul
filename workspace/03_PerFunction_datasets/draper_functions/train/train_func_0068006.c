gst_mpdparser_free_representation_node (GstRepresentationNode *
    representation_node)
{
  if (representation_node) {
    if (representation_node->id)
      xmlFree (representation_node->id);
    g_strfreev (representation_node->dependencyId);
    g_strfreev (representation_node->mediaStreamStructureId);
    gst_mpdparser_free_representation_base_type
        (representation_node->RepresentationBase);
    g_list_free_full (representation_node->SubRepresentations,
        (GDestroyNotify) gst_mpdparser_free_subrepresentation_node);
    gst_mpdparser_free_seg_base_type_ext (representation_node->SegmentBase);
    gst_mpdparser_free_segment_template_node
        (representation_node->SegmentTemplate);
    gst_mpdparser_free_segment_list_node (representation_node->SegmentList);
    g_list_free_full (representation_node->BaseURLs,
        (GDestroyNotify) gst_mpdparser_free_base_url_node);
    g_slice_free (GstRepresentationNode, representation_node);
  }
}
