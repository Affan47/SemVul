gst_mpdparser_free_segment_template_node (GstSegmentTemplateNode *
    segment_template_node)
{
  if (segment_template_node) {
    if (segment_template_node->media)
      xmlFree (segment_template_node->media);
    if (segment_template_node->index)
      xmlFree (segment_template_node->index);
    if (segment_template_node->initialization)
      xmlFree (segment_template_node->initialization);
    if (segment_template_node->bitstreamSwitching)
      xmlFree (segment_template_node->bitstreamSwitching);

    gst_mpdparser_free_mult_seg_base_type_ext
        (segment_template_node->MultSegBaseType);
    g_slice_free (GstSegmentTemplateNode, segment_template_node);
  }
}
