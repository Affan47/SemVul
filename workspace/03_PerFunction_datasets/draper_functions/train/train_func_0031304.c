gst_cmml_parser_node_to_string (GstCmmlParser * parser, xmlNodePtr node)
{
  xmlBufferPtr xml_buffer;
  xmlDocPtr doc;
  guchar *str;

  if (parser)
    doc = parser->context->myDoc;
  else
    doc = NULL;

  xml_buffer = xmlBufferCreate ();
  xmlNodeDump (xml_buffer, doc, node, 0, 0);
  str = xmlStrndup (xml_buffer->content, xml_buffer->use);
  xmlBufferFree (xml_buffer);

  return str;
}
