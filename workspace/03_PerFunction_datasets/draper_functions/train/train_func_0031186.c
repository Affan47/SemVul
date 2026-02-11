gst_mpdparser_free_subset_node (GstSubsetNode * subset_node)
{
  if (subset_node) {
    if (subset_node->contains)
      xmlFree (subset_node->contains);
    g_slice_free (GstSubsetNode, subset_node);
  }
}
