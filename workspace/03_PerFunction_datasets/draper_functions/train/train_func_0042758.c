gst_matroska_parse_set_index (GstElement * element, GstIndex * index)
{
  GstMatroskaParse *parse = GST_MATROSKA_PARSE (element);

  GST_OBJECT_LOCK (parse);
  if (parse->common.element_index)
    gst_object_unref (parse->common.element_index);
  parse->common.element_index = index ? gst_object_ref (index) : NULL;
  GST_OBJECT_UNLOCK (parse);
  GST_DEBUG_OBJECT (parse, "Set index %" GST_PTR_FORMAT,
      parse->common.element_index);
}
