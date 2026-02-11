gst_aac_parse_pre_push_frame (GstBaseParse * parse, GstBaseParseFrame * frame)
{
  GstAacParse *aacparse = GST_AAC_PARSE (parse);


  if (aacparse->header_type == DSPAAC_HEADER_ADTS
      && aacparse->output_header_type == DSPAAC_HEADER_NONE) {
    guint header_size;
    GstMapInfo map;
    gst_buffer_map (frame->buffer, &map, GST_MAP_READ);
    header_size = (map.data[1] & 1) ? 7 : 9;
    gst_buffer_unmap (frame->buffer, &map);
    gst_buffer_resize (frame->buffer, header_size,
        gst_buffer_get_size (frame->buffer) - header_size);
  }

  return GST_FLOW_OK;
}
