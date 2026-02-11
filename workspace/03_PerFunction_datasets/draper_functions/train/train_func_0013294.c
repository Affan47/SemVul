gst_mpdparser_free_subrepresentation_node (GstSubRepresentationNode *
    subrep_node)
{
  if (subrep_node) {
    gst_mpdparser_free_representation_base_type
        (subrep_node->RepresentationBase);
    if (subrep_node->dependencyLevel)
      xmlFree (subrep_node->dependencyLevel);
    g_strfreev (subrep_node->contentComponent);
    g_slice_free (GstSubRepresentationNode, subrep_node);
  }
}
