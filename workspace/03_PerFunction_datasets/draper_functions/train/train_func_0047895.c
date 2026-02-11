gst_mpdparser_free_segment_url_node (GstSegmentURLNode * segment_url)
{
  if (segment_url) {
    if (segment_url->media)
      xmlFree (segment_url->media);
    g_slice_free (GstRange, segment_url->mediaRange);
    if (segment_url->index)
      xmlFree (segment_url->index);
    g_slice_free (GstRange, segment_url->indexRange);
    g_slice_free (GstSegmentURLNode, segment_url);
  }
}
