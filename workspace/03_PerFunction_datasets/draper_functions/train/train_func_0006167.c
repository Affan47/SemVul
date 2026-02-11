gst_cmml_parser_tag_object_to_string (GstCmmlParser * parser, GObject * tag)
{
  guchar *tag_string = NULL;
  GType tag_type = G_OBJECT_TYPE (tag);

  if (tag_type == GST_TYPE_CMML_TAG_STREAM)
    tag_string = gst_cmml_parser_tag_stream_to_string (parser,
        GST_CMML_TAG_STREAM (tag));
  else if (tag_type == GST_TYPE_CMML_TAG_HEAD)
    tag_string = gst_cmml_parser_tag_head_to_string (parser,
        GST_CMML_TAG_HEAD (tag));
  else if (tag_type == GST_TYPE_CMML_TAG_CLIP)
    tag_string = gst_cmml_parser_tag_clip_to_string (parser,
        GST_CMML_TAG_CLIP (tag));
  else
    g_warning ("could not convert object to cmml");

  return tag_string;
}
